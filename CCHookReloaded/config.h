#pragma once

struct SConfig
{
	const char *pakName = "cch";

	// Pickup Chams (Med & Ammo Packs)
	bool pickupChams = true;
	bool pickupChamsFillWallhack = false;
	bool pickupChamsOutline = true;
	bool pickupChamsOutlineWallhack = true;
	vec4_t colorHealth = { 230, 0, 255, 255 };
	vec4_t colorHealthOutline = { 255, 255, 255, 255 };
	vec4_t colorAmmo = { 0, 0, 255, 255 };
	vec4_t colorAmmoOutline = { 255, 255, 255, 255 };

	// Dropped Weapon Chams
	bool droppedWeaponChams = true;
	bool droppedWeaponChamsFillWallhack = false;
	bool droppedWeaponChamsOutline = true;
	bool droppedWeaponChamsOutlineWallhack = true;
	vec4_t colorWorldWeapons = { 0, 255, 0, 255 };
	vec4_t colorWorldWeaponsOutline = { 255, 255, 255, 255 };

	qhandle_t& itemshader1 = media.glowChamsShader;
	qhandle_t& itemshader2 = media.ocrystalShader;

	// Missile Chams
	bool missileChams = true;
	vec4_t missileVisRGBA = { 255, 0, 0, 0 };
	vec4_t missileInvRGBA = {  80, 0, 0, 0 };

	// Player Chams
	bool playerChams = true;
	bool playerOutlineChams = false;
	bool playerCorpseChams = true;
	vec4_t playerVulnRGBA   = { 255, 0, 0,   0 };
	vec4_t playerInvulnRGBA = { 255, 0, 255, 0 };
	qhandle_t& playerShader = media.coverShader;

	// Held Weapon Chams
	bool heldWeaponChams = true;
	bool weaponChamsShader1Wallhack = false;
	bool weaponChamsShader2Wallhack = true;
	vec4_t colorTeamWeapon = { 255, 255, 0, 255 };
	vec4_t colorTeamWeaponOutline = { 0, 255, 255, 255 };
	qhandle_t& weaponshader1 = media.glowChamsShader;
	qhandle_t& weaponshader2 = media.ocrystalShader;

	// Visuals
	// bool scopedWalk = true; Removed for now
	bool noScopeFov = false;
	bool noScopeBlackout = true;
	bool bulletTracers = false;
	bool grenadeTrajectory = true;
	bool noDamageFeedback = true;
	bool noCamExplosionShake = true;
	bool noSmoke = true;
	bool noFoliage = true;
	bool noWeather = true;

	/* Key list for aimbotAimkey:

	 * VK_LBUTTON		(Left Mouse / Mouse1)
	 * VK_RBUTTON		(Right Mouse / Mouse2)
	 * VK_MBUTTON		(Middle Mouse / Mouse3 / Scroll Wheel Click)
	 * VK_XBUTTON1		(Side Button / Mouse4)
	 * VK_XBUTTON2		(Side Button / Mouse5)
	 * 0				(No Aimkey - Aimbot always on)

	*/	

	// Aimbot
	bool aimbotEnabled = true;
	int  aimbotAimkey = VK_XBUTTON2; // Change using the list above
	bool aimbotStickyAim = true;
	bool aimbotStickyAutoReset = true;
	bool aimbotLockViewangles = true;
	bool aimbotAutoshoot = false;
	bool aimbotVelocityPrediction = false;
	bool aimbotPingPrediction = false;
	bool aimbotHumanAim = false;
	float aimbotHumanFovX = 10.0f;
	float aimbotHumanFovY = 15.0f;
	float aimbotHumanFovMaxX = 5.0f;
	float aimbotHumanFovMaxY = 10.0f;
	float aimbotHumanSpeed = 0.0666f;
	float aimbotHeadBoxTraceStep = 0.5f;
	float aimbotBodyBoxTraceStep = 0.3f;
	float aimbotHeadHeightOffset = 0.0f; // -5.0f aims roughly at the neck
	bool aimbotAutoCrouch = true;
	float aimbotAutoCrouchOffset = 21.0f;


	// Spoofer
	// nullptr:	do not spoof
	// string:	spoof to that value, fill '?' with random hex chars
	const char *etproGuid = "????????????????????????????????????????"; //SHA1 hash, uppercase
	const char *nitmodMac = "04-92-26-??-??-??"; // MAC Address, uppercase, byte separation: '-'
	uint32_t spoofSeed = 0; // 0 = Random each game start


	// Misc
	bool spectatorWarning = true;
	bool enemySpawnTimer = true;
	bool customDmgSounds = true;
	bool quickUnbanReconnect = true; // F10
	bool cleanScreenshots = true;
	bool cvarUnlocker = false; // Might be detected by some Anti-Cheats
	bool picmipHack = false; // Visible on Screenshots
	bool bunnyHop = true;


	// ESP
	bool headBbox = true;
	bool bodyBbox = false;
	bool boneEsp = true;
	bool nameEsp = false;
	int nameEspMode = 0; // 0 = Anchor Feet, 1 = Anchor Head
	bool missileEsp = true;
	bool missileRadius = false;
	bool pickupEsp = true;
	vec4_t& iconEspColor = colorWhite;
	float maxEspDistance = FLT_MAX;
};

inline SConfig cfg;
