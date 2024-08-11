# Disclaimer
Educational purposes only! 
# How to use open horse:
1. Build soultion in Visual Studio (ctrl+shift+b), output DLL will be in the x64 debug or release folder
2. Download process hacker <https://processhacker.sourceforge.io/>
3. Start the game, then find it in process hacker 
4. Right-click on the process -> miscellaneous -> inject DLL Select your open_horse.dll and open it
5. A console window will be attached to the game, enter your commands there
----
# Commands

* cam - toggles free camera view
* dump - dumps all the item IDs (item_dump.txt in game directory)
* {item_id} {amount} - add (positive amount) or remove (negative amount) items in the backpack
* {script_command} - execute a script
* exit - unload mod
---
# Scripts

Main:

    global/Sky.SetSkyModifierSkyColor(0, 0, 0, 1.0); ---sky visual
    global/Sky.SetSkyModifierHorizonColor(0, 0, 0, 1.0); ---sky visual
    global/Sky.SetSkyModifierColorMix(0); ---sky visual
    global/Sky.StartSkyModifier(32); ---sky visual
    /World.SetWorldDrawGlobalSpace(0); --- xray
    /World.SetWorldDrawGlobalSpace(1); ---xray
    global/CutSceneCamera.Start();global/CutSceneCamera.Move(global/Player);global/CutSceneCamera.SetOrientationByObject(global/Player);global/CutSceneCamera.AddPosition(0, 0.5, -0.5); ---first person
    global/Player/Camera.Start(); ---restore third person
    global/Horse.CloneHorseAppearance(0); ---clientside horse appearance
    global/HorseForSaleInfoWindow/RenderViews/RenderTargetView/Scene/Animation/Horse.CloneHorse(0, 0);global/HorseForSaleInfoWindow/RenderViews/RenderTargetView/Scene/Animation/Horse.HorseForSaleStartBuyWindow(); ---horse buy window
    global/Horse.HorseRestoreAppearance(); ---restore horse
    global/GlobalTimer.SetTimerTime(12); --- day time
    global/ForcePlayerFromRestrictedArea.Delete();global/ForcePlayerBackToMoorland.Delete();global/GlobalSpaceObjects/WorldBlockCollsion.Delete(); ---bypass restricted area
    global/Horse.SetHorseMaxFallTime(99999); ---bypass fall damage
    global/SwimActionBar.Delete(); --- bypass swim timer

Expansive:
    
    global/QuestManager.QuestManagerDiscardSelected(); --- discard quest
    global/MyStableWindow.Start(); ---- open wardrobe
    global/MakeupChangeWindow.Start(); --- open makeup
    global/HairStyleChangeWindow.Start(); ---- open hairstyle
    global/QuestManager/Episode1/Chain2330/E01_Quest_L01_C2330_050.QuestComplete();  --- js
    global/QuestManager/Episode1/Chain2137/E01_Quest_L01_C2137_005.QuestComplete(); --- horse xp
    global/QuestManager/Episode1/Chain2321/E01_Quest_L18_C2321_007.QuestComplete(); --- player xp
    global/Network.NetworkHorseFreeWellbeing(); --- horse care
    
Old shops:

    global/ShopManager/Episode1/ValentinesDayShop2018.ShopOpen(); ---valentines
    global/ShopManager/Episode1/EquestrianFestival_Premium_FestiveEquestrian.ShopOpen(); ---EQ 1
    global/ShopManager/Episode1/EquestrianFestival_TokenVendor_ClassicEquestrian.ShopOpen(); ---EQ2
    global/ShopManager/Episode1/EquestrianFestival_Premium_EclecticEquestrian.ShopOpen(); ---EQ3
    global/ShopManager/Episode1/BeachPartyShop.ShopOpen(); ---Beach shop
    global/ShopManager/Episode1/BlackFridayShop_2022.ShopOpen(); ---Black friday shop
    global/ShopManager/Episode1/CloudKingdom_ExplorerShop.ShopOpen(); ---cloud kingdom
    global/ShopManager/Episode1/EasterShop.ShopOpen(); ---easter 1
    global/ShopManager/Episode1/EasterShop2.ShopOpen(); ---easter 2
    global/ShopManager/Episode1/HalloweenShop.ShopOpen(); ---halloween shop
    global/ShopManager/Episode1/HalloweenConsumablesShop.ShopOpen(); ---halloween consumables
    global/ShopManager/Episode1/HalloweenPetShop.ShopOpen(); ---halloween pet
    global/ShopManager/Episode1/HalloweenMaskShop.ShopOpen(); ---halloween mask
    global/ShopManager/Episode1/HalloweenFest_VintageShop.ShopOpen(); ---halloween vintage
    global/ShopManager/Episode1/MidsummerShop.ShopOpen(); ---midsummer1
    global/ShopManager/Episode1/MidsummerShop_02.ShopOpen(); ---midsummer2
    global/ShopManager/Episode1/NewYearShop.ShopOpen(); ---newyear
    global/ShopManager/Episode1/RainbowFest_Shopkeeper_PrideShop.ShopOpen(); ---rainbow fest
    global/ShopManager/Episode1/StarStableBirthdayShop.ShopOpen(); --- bday1
    global/ShopManager/Episode1/StarStableBirthdayGearShop.ShopOpen(); ---bday2
    global/ShopManager/Episode1/JojoSiwaShop.ShopOpen(); ---jojo siwa
    global/ShopManager/Episode1/MagicChristmasMarketShop_A.ShopOpen(); --- christmas market shop
    global/ShopManager/Episode1/MagicChristmasMarketShop_Costumes.ShopOpen(); ---christmas costumes
    global/ShopManager/Episode1/MagicChristmasMarketShop_ChristmasSweaters.ShopOpen(); ---christmas sweater
    global/ShopManager/Episode1/WinterVillage_Pets.ShopOpen(); ---christmas pets
    global/ShopManager/Episode1/SpiritHorseShop.ShopOpen(); ---spirit shop open

Pets:

    global/ShopManager/Episode1/MagicPetShopCrystalCat01.ShopOpen(); ---Crystal cat 1
    global/ShopManager/Episode1/MagicPetShopCrystalCat02.ShopOpen(); ---crystal cat 2
    global/ShopManager/Episode1/MagicPetShopFishCat01.ShopOpen(); ---fish cat 1
    global/ShopManager/Episode1/MagicPetShopFishCat02.ShopOpen(); ---fish cat 2
    global/ShopManager/Episode1/MagicPetShopManta01.ShopOpen(); ---manta 1
    global/ShopManager/Episode1/MagicPetShopManta02.ShopOpen(); ---manta 2
    global/ShopManager/Episode1/MagicPetShopManta03.ShopOpen(); ---manta 3
    global/ShopManager/Episode1/MagicPetShopManta04.ShopOpen(); ---manta 4

Horse appearance:
            
    global/Horse.HorseAppearanceCustomBody(1,1,0);global/Horse.HorseAppearanceCustomHair(15,1,0); ---old gray deer
    global/Horse.HorseAppearanceCustomBody(1,2,0);global/Horse.HorseAppearanceCustomHair(15,1,0); ---old white deer
    global/Horse.HorseAppearanceCustomBody(1,3,0);global/Horse.HorseAppearanceCustomHair(15,1,0); ---old rudolph deer
    global/Horse.HorseAppearanceCustomBody(1,4,0);global/Horse.HorseAppearanceCustomHair(15,1,0); ---old brown deer
    global/Horse.HorseAppearanceCustomBody(1,1,0);global/Horse.HorseAppearanceCustomHair(20,1,0); ---yule goat
    global/Horse.HorseAppearanceCustomBody(1,1,0);global/Horse.HorseAppearanceCustomHair(22,1,0); ---female deer
    global/Horse.HorseAppearanceCustomBody(1,1,0);global/Horse.HorseAppearanceCustomHair(23,1,0); ---bear
    global/Horse.HorseAppearanceCustomBody(1,1,0);global/Horse.HorseAppearanceCustomHair(24,1,0); ---moose

Reputation:

    global/FactionManager/AAExpedition.FactionSetReputation(6001); ---AAExpedition
    global/FactionManager/AncientOak.FactionSetReputation(6001); ---AncientOak
    global/FactionManager/ArcheologyDepartment.FactionSetReputation(6001); ---ArcheologyDepartament
    global/FactionManager/BaronessRacetrack.FactionSetReputation(6001); ---Baroness Racetrack
    global/FactionManager/BeatrixTrust.FactionSetReputation(6001); ---BeatrixTrust
    global/FactionManager/BigBonnyMachine_HORSE.FactionSetReputation(6001); ---BigBonnyMachine_HORSE
    global/FactionManager/BillysFlowers.FactionSetReputation(6001); ---BillysFlowers
    global/FactionManager/BobCatGirls.FactionSetReputation(6001); ---BobCatGirls
    global/FactionManager/ButtergoodFamily.FactionSetReputation(6001); ---ButtergoodFamily
    global/FactionManager/ChampionshipFortPinta.FactionSetReputation(6001); ---ChampionshipFortPinta
    global/FactionManager/ChampionshipMoorland.FactionSetReputation(6001); ---ChampionshipMoorland
    global/FactionManager/ChampionshipPony.FactionSetReputation(6001); ---ChampionshipPony
    global/FactionManager/CrescentVillage.FactionSetReputation(6001); ---CrescentVillage
    global/FactionManager/Druids.FactionSetReputation(6001); ---Druids
    global/FactionManager/FamilyDew.FactionSetReputation(6001); ---FamilyDew
    global/FactionManager/FamilyGoldspur.FactionSetReputation(6001); ---FamilyGoldspur
    global/FactionManager/FamilyJarlasson.FactionSetReputation(6001); ---FamilyJarlasson
    global/FactionManager/FamilySunfield.FactionSetReputation(6001); ---FamilySunfield
    global/FactionManager/ForgottenFieldsStable.FactionSetReputation(6001); ---ForgottenFieldsStable
    global/FactionManager/FortMaria.FactionSetReputation(6001); ---FortMaria
    global/FactionManager/FortPinta.FactionSetReputation(6001); ---FortPinta
    global/FactionManager/GED_JarlaheimOffice.FactionSetReputation(6001); ---GED_JarlaheimOffice
    global/FactionManager/Goldenleafs.FactionSetReputation(6001); ---Goldenleafs
    global/FactionManager/JamieOlivetree.FactionSetReputation(6001); ---JamieOlivetree
    global/FactionManager/JorvikCityCitizen.FactionSetReputation(6001); ---JorvikCityCitizen
    global/FactionManager/JorvikFishingClub.FactionSetReputation(6001); ---JorvikFishingClub
    global/FactionManager/JorvikGazette.FactionSetReputation(6001); ---JorvikGazette
    global/FactionManager/JorvikRangersDundull.FactionSetReputation(6001); ---JorvikRangersDundull
    global/FactionManager/JorvikRangersRedwoodPoint.FactionSetReputation(6001); ---JorvikRangersRedwoodPoint
    global/FactionManager/JorvikStable.FactionSetReputation(6001); ---JorvikStable
    global/FactionManager/MoorlandBridgeBuilders.FactionSetReputation(6001); ---MoorlandBridgeBuilders
    global/FactionManager/RickyWinterwell.FactionSetReputation(6001); ---RickyWinterwell
    global/FactionManager/ShoppingMall.FactionSetReputation(6001); ---ShoppingMall
    global/FactionManager/SilvergladeVillage.FactionSetReputation(6001); ---SilvergladeVillage
    global/FactionManager/SilvergladeWinery.FactionSetReputation(6001); ---SilvergladeWinery
    global/FactionManager/SouthHarvestCounties.FactionSetReputation(6001); ---SouthHarvestCounties
    global/FactionManager/SouthHoof.FactionSetReputation(6001); ---SouthHoof
    global/FactionManager/SouthHoofHermit.FactionSetReputation(6001); ---SouthHoofHermit
    global/FactionManager/SouthJorvikFishingClub.FactionSetReputation(6001); ---SouthJorvikFishingClub
    global/FactionManager/Stoneground_Expedition.FactionSetReputation(6001); ---Stoneground_Expedition
    global/FactionManager/WildwoodsForesters.FactionSetReputation(6001); ---WildwoodsForesters
    global/FactionManager/WildwoodsMystics.FactionSetReputation(6001); ---WildwoodsMystics
    global/FactionManager/WildwoodsWarriors.FactionSetReputation(6001); ---WildwoodsWarriors
    global/FactionManager/WinterwellFamily.FactionSetReputation(6001); ---WinterwellFamily
    global/FactionManager/WolfHellInn.FactionSetReputation(6001); ---WolfHellInn
    global/FactionManager/SoulRidingWithRhiannon.FactionAddReputation(); ---rhiannon rep for runerunner (370ID of runerunner)

Other:

    global/GMUI.FileObjectLoad();global/GMUI/Timer.SetActive(0);global/GMWindow.Start(); ---game master menu
    global/Player.PlayerTPNetPlayAnimation("ActionMine"); ---(use gamemaster)
    global/Player.PlayerTPNetPlayAnimationLooping("SitSunChair"); ---(use gamemaster)
    global/Player.PlayerTPNetPlayAnimationEnd(); ---ends animation (use gamemaster)
    global/ShopManager/Episode1/HorseHairStyleShop1.ShopOpen(); ---Mane change5
