#include <windows.h>
#include <stdio.h>	
#include <emmintrin.h>

typedef char s8_t;
typedef short s16_t;
typedef int s32_t;
typedef long long s64_t;

typedef unsigned char u8_t;
typedef unsigned short u16_t;
typedef unsigned int u32_t;
typedef unsigned long long u64_t;

typedef struct s_actor_t {
	u64_t m_vtable;
	u64_t m_value;
} s_actor_t;

typedef struct s_set_t {
	u64_t m_vtable;
	u64_t m_value_a;
	u64_t m_value_b;
} s_set_t;

// text
static u64_t(__fastcall* get_item_fn)     (u64_t item_manager, u32_t id); // 0x121B00 get item
static wchar_t* (__fastcall* item_name_fn)    (u64_t item); // 0x1AABF0 get item name
static u8_t(__fastcall* add_item_fn)     (u64_t item_manager, u64_t item, u32_t count, u8_t unk); // 0x26CBF0 add item
static u64_t(__fastcall* get_scripts_fn)  (u64_t studio); // 0x51EC60 get scripts function
static u64_t(__fastcall* find_s_actor_fn) (u64_t finder, s_actor_t* out, s_set_t*, s8_t* name, s_actor_t*, s_actor_t*, u64_t, u64_t, u64_t); // 0x4F73B0 find actor safe
static u8_t(__fastcall* s_actor_run)     (u64_t scripts, s8_t* script, s_actor_t* actor, s_actor_t* safe, u64_t script_last); // 0x5B7080 actor run script

// data
static u64_t item_manager;	   // 0xFC6538
static u64_t cam_manager;	   // 0xFBC4D0
static u64_t actor_manager;   // 0xFBC4C8
static u64_t studio;			   // 0xFBC468
static u64_t script_vtbl;	   // 0xC48C4E
static u64_t s_ptr_vtbl;	   // 0xC48C58

#define rva(address, offset) address + (s32_t)((*(s32_t*)(address + offset) + offset) + sizeof(s32_t))

u32_t mod_size(u64_t base) {
	IMAGE_DOS_HEADER* dos_head = (IMAGE_DOS_HEADER*)(base);
	IMAGE_NT_HEADERS* nt_head = (IMAGE_NT_HEADERS*)(base + dos_head->e_lfanew);

	return nt_head->OptionalHeader.SizeOfImage;
}

u32_t str_cmp(s8_t* str, s8_t* sub_str) {
	for (; *str && *sub_str; str++, sub_str++)
		if (*str != *sub_str)
			return 0;

	return 1;
}

u64_t find_pattern(u32_t rel, s8_t* pattern, u64_t base, u32_t size) {
	// convert from ida style pattern
	u32_t sig_len = 1;
	for (s8_t* sig_curs = pattern; *sig_curs; sig_curs++)
		if (*sig_curs == ' ')
			sig_len++;

	sig_len += sizeof(u64_t) - (sig_len % sizeof(u64_t));

	s8_t* sig = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sig_len);
	s8_t* mask = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sig_len);;

	for (s8_t* sig_curs = pattern, i = 0; *sig_curs; ) {
		if (*sig_curs == ' ') {
			sig_curs++;
		}
		else if (*sig_curs == '?') {
			sig_curs++;
			i++;
		}
		else {
			sig[i] = strtol(sig_curs, 0, 16);
			mask[i] = 0xff;
			sig_curs += 2;
			i++;
		}
	}

	// find pattern in module
	u64_t result = 0;
	u64_t sig_cmp_len = sig_len / sizeof(u64_t);
	__m128i byte_mask = _mm_set1_epi8(*sig);

	for (u32_t offset = 0; offset < size - sizeof(__m128i); ) {
		s32_t found = _mm_movemask_epi8(_mm_cmpeq_epi8(_mm_loadu_si128((__m128i*)(base + offset)), byte_mask));

		if (found) {
			offset += _tzcnt_u32(found);

			for (u32_t x = 0; x < sig_cmp_len; x++) {
				u64_t mem = *(u64_t*)(base + offset + x * sizeof(u64_t));
				u64_t sig_step = *(u64_t*)(sig + sizeof(u64_t) * x);
				u64_t mask_step = *(u64_t*)(mask + sizeof(u64_t) * x);

				if ((mem ^ sig_step) & mask_step) {
					goto next;
				}
			}

			result = base + offset;
			break;

		next:
			offset++;
		}
		else {
			offset += sizeof(__m128i);
		}
	}

	HeapFree(GetProcessHeap(), 0, sig);
	HeapFree(GetProcessHeap(), 0, mask);

	return rel && result ? rva(result, rel) : result;
}

s_actor_t actor_find(s8_t* path) {
	s_set_t safe_1 = { s_ptr_vtbl, 0, 0 };
	s_actor_t safe_2 = { s_ptr_vtbl, 0xBADF00D };
	s_actor_t safe_3 = { s_ptr_vtbl, 0xBADF00D };

	s_actor_t res;
	find_s_actor_fn(actor_manager, &res, &safe_1, path, &safe_2, &safe_3, 0, 0, 0);
	return res;
}

u32_t script_run(s8_t* path, s8_t* script) {
	s_actor_t actor = actor_find(path);
	s_actor_t safe = { s_ptr_vtbl, 0xBADF00D };
	return s_actor_run(get_scripts_fn(studio), script, &actor, &safe, script_vtbl);
}

void dump_items() {
	FILE* items_dump = fopen("item_dump.txt", "wb");
	for (u32_t i = 0; i != 20000; i++) {
		u64_t item = get_item_fn(item_manager, i);
		if (!item) {
			continue;
		}

		wchar_t* wch = item_name_fn(item);
		if (!wch) {
			continue;
		}

		s8_t item_s8[0x100];
		memset(item_s8, 0, sizeof(item_s8));
		for (wchar_t* curs = wch; *curs; curs++) {
			item_s8[curs - wch] = (s8_t)(*curs);
		}

		s8_t dump_line[0x100];
		sprintf(dump_line, "%d - %s\n", i, item_s8);
		fwrite(dump_line, 1, strlen(dump_line), items_dump);
	}

	fclose(items_dump);
}

void item_operation(s8_t* input) {
	s32_t id, count;
	sscanf(input, "%d %d", &id, &count);

	u64_t item = get_item_fn(item_manager, id);
	if (!item) {
		printf("invalid item\n");
		return;
	}

	if (count > 0) {
		add_item_fn(item_manager, item, count, 0);
	}
	else {
		s8_t rem_script[0x100];
		sprintf(rem_script, "this.InventoryViewRemovePlayerItemCount(%d, %d);", id, -count);
		script_run("global/BackpackInventoryView", rem_script);
	}
}

u32_t __stdcall mod_entry(void* module_handle) {
	AllocConsole();
	FILE* out_fd = freopen("CONOUT$", "w", stdout);
	FILE* in_fd = freopen("CONIN$", "r", stdin);

	u64_t base = GetModuleHandleA(0);
	u32_t size = mod_size(base);

	// text
	get_item_fn = find_pattern(0x1, "E8 ? ? ? ? 48 8B F8 85 F6", base, size);
	item_name_fn = find_pattern(0x1, "E8 ? ? ? ? 48 8B D8 33 D2 48 8D 4C 24 50", base, size);
	add_item_fn = find_pattern(0x1, "E9 ? ? ? ? CC CC CC CC CC CC CC CC C6 05 ? ? ? ? ?", base, size);
	get_scripts_fn = find_pattern(0x1, "E8 ? ? ? ? 48 8D 48 30", base, size);
	find_s_actor_fn = find_pattern(0x1, "E8 ? ? ? ? 48 8B D8 8D 55 01", base, size);
	s_actor_run = find_pattern(0x1, "E8 ? ? ? ? 48 8B 5C 24 78 48 83 C4 ? 5F 5E 5D C3 CC", base, size);

	// data
	item_manager = *(u64_t*)find_pattern(0x3, "48 8B 3D ? ? ? ? 49 8B CC", base, size);
	cam_manager = *(u64_t*)find_pattern(0x3, "48 8B 0D ? ? ? ? 0F 11 45 40", base, size);
	actor_manager = *(u64_t*)find_pattern(0x3, "48 8B 1D ? ? ? ? 4C 8D 3D ? ? ? ? 4C 89 7D C7", base, size);
	studio = *(u64_t*)find_pattern(0x3, "48 8B 0D ? ? ? ? 48 85 C9 0F 84 ? ? ? ? E8 ? ? ? ? 48 8B F8 48 85 C0", base, size);
	script_vtbl = find_pattern(0x3, "48 8D 0D ? ? ? ? 48 89 4C 24 20 4C 8D 4C 24 30", base, size);
	s_ptr_vtbl = find_pattern(0x3, "4C 8D 0D ? ? ? ? 4C 89 8A F8 06 00 00", base, size);

	s8_t* user_input = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, 0x1000);

	while (1) {
		// read user input
		if (!fgets(user_input, 0x1000, stdin))
			continue;

		if (str_cmp(user_input, "exit")) {
			break;
		}
		else if (str_cmp(user_input, "dump")) {
			dump_items();
		}
		else if (str_cmp(user_input, "cam")) {
			*(u8_t*)(cam_manager + 0x9E) = !(*(u8_t*)(cam_manager + 0x9E)); // C6 81 ? ? 00 00 ? 48 8B 0D ? ? ? ? 48 8D ?
		}
		else if (*user_input >= 0x30 && *user_input <= 0x39) { // is a number
			item_operation(user_input);
		}
		else {
			script_run("global/Horse", user_input); // TODO: variable actor context, call from main thread to prevent crashes
		}
	}

	HeapFree(GetProcessHeap(), 0, user_input);

	fclose(out_fd);
	fclose(in_fd);
	FreeConsole();

	FreeLibraryAndExitThread(module_handle, 0);
}

s32_t __stdcall DllMain(void* module_handle, u32_t call_reason, void* reserved) {
	if (call_reason == DLL_PROCESS_ATTACH)
		CreateThread(0, 0, mod_entry, module_handle, 0, 0);

	return 1;
}
