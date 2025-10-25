#include "pch.h"
#include "globals.h"
#include "ui.h"

#include "config.h"

namespace ui
{
	static int16_t btnDelete = 0, btnMouseL = 0;

	void AdjustFrom640(float *x, float *y, float *w, float *h)
	{
		*x *= cg_glconfig.vidWidth / 640.0f;
		*y *= cg_glconfig.vidHeight / 480.0f;

		*w *= cg_glconfig.vidWidth / 640.0f;
		*h *= cg_glconfig.vidHeight / 480.0f;
	}
	bool WorldToScreen(const vec3_t worldCoord, float *x, float *y)
	{
		vec3_t trans;
		VectorSubtract(worldCoord, cg_refdef.vieworg, trans);

		// z = how far is the object in our forward direction, negative = behind/mirrored
		float z = DotProduct(trans, cg_refdef.viewaxis[0]);
		if (z <= 0.001)
			return false;

		float xc = 640.0 / 2.0;
		float yc = 480.0 / 2.0;

		float px = tan(cg_refdef.fov_x * (M_PI / 360));
		float py = tan(cg_refdef.fov_y * (M_PI / 360));

		*x = xc - DotProduct(trans, cg_refdef.viewaxis[1])*xc/(z*px);
		*y = yc - DotProduct(trans, cg_refdef.viewaxis[2])*yc/(z*py);

		return true;
	}
	void DrawLine2D(float x0, float y0, float x1, float y1, float f, const vec4_t color)
	{
		ui::AdjustFrom640(&x0, &y0, &x1, &y1);

		vec2_t org;
		org[0] = (x0+x1)/2.0f;
		org[1] = (y0+y1)/2.0f;

		float w = sqrt((x1-x0)*(x1-x0)+(y1-y0)*(y1-y0));
		float angle = atan2((x1-x0), (y1-y0));

		polyVert_t verts[4];
		SetupRotatedThing(verts, org, w, f, angle);

		// Set color for all vertices
		for (size_t i = 0; i < std::size(verts); i++)
		{
			verts[i].modulate[0] = color[0] * 255;
			verts[i].modulate[1] = color[1] * 255;
			verts[i].modulate[2] = color[2] * 255;
			verts[i].modulate[3] = 255;
		}
	
		DoSyscall(CG_R_DRAW2DPOLYS, verts, 4, media.whiteShader);
	}
	void DrawLine3D(const vec3_t from, const vec3_t to, float f, const vec4_t col)
	{
		float fromX, fromY, 
			toX, toY;

		if (WorldToScreen(from, &fromX, &fromY) && WorldToScreen(to, &toX, &toY))
			DrawLine2D(fromX, fromY, toX, toY, f, col);
	}
	void DrawBox2D(float x, float y, float w, float h, const vec4_t color, qhandle_t shader)
	{
		AdjustFrom640(&x, &y, &w, &h);

		DoSyscall(CG_R_SETCOLOR, color);
		DoSyscall(CG_R_DRAWSTRETCHPIC, x, y, w, h, 0.0f, 0.0f, 1.0f, 1.0f, shader);
		DoSyscall(CG_R_SETCOLOR, nullptr);
	}
	void DrawBox3D(const vec3_t mins, const vec3_t maxs, float f, const vec4_t color)
	{
		vec3_t boundingBox[] =
		{
			{ maxs[0], maxs[1], maxs[2] },
			{ maxs[0], maxs[1], mins[2] },
			{ mins[0], maxs[1], mins[2] },
			{ mins[0], maxs[1], maxs[2] },
			{ maxs[0], mins[1], maxs[2] },
			{ maxs[0], mins[1], mins[2] },
			{ mins[0], mins[1], mins[2] },
			{ mins[0], mins[1], maxs[2] }
		};

		//Upper rect
		DrawLine3D(boundingBox[0], boundingBox[1], f, color);
		DrawLine3D(boundingBox[0], boundingBox[3], f, color);
		DrawLine3D(boundingBox[2], boundingBox[1], f, color);
		DrawLine3D(boundingBox[2], boundingBox[3], f, color);

		//Upper to lower rect
		DrawLine3D(boundingBox[0], boundingBox[4], f, color);
		DrawLine3D(boundingBox[1], boundingBox[5], f, color);
		DrawLine3D(boundingBox[2], boundingBox[6], f, color);
		DrawLine3D(boundingBox[3], boundingBox[7], f, color);

		//Lower rect
		DrawLine3D(boundingBox[4], boundingBox[5], f, color);
		DrawLine3D(boundingBox[4], boundingBox[7], f, color);
		DrawLine3D(boundingBox[6], boundingBox[5], f, color);
		DrawLine3D(boundingBox[6], boundingBox[7], f, color);
	}
	void DrawBoxBordered2D(float x, float y, float w, float h, const vec4_t fillColor, const vec4_t borderColor, qhandle_t shader)
	{
		const float borderSize = 1.0f;

		AdjustFrom640(&x, &y, &w, &h);

		DoSyscall(CG_R_SETCOLOR, fillColor);
		DoSyscall(CG_R_DRAWSTRETCHPIC, x, y, w, h, 0.0f, 0.0f, 0.0f, 1.0f, shader);
	
		DoSyscall(CG_R_SETCOLOR, borderColor);
		DoSyscall(CG_R_DRAWSTRETCHPIC, x-borderSize, y-borderSize, w+borderSize*2, borderSize, 0.0f, 0.0f, 0.0f, 1.0f, shader);
		DoSyscall(CG_R_DRAWSTRETCHPIC, x-borderSize, y+h, w+borderSize*2, borderSize, 0.0f, 0.0f, 0.0f, 1.0f, shader);
		DoSyscall(CG_R_DRAWSTRETCHPIC, x-borderSize, y, borderSize, h, 0.0f, 0.0f, 0.0f, 1.0f, shader);
		DoSyscall(CG_R_DRAWSTRETCHPIC, x+w, y, borderSize, h, 0.0f, 0.0f, 0.0f, 1.0f, shader);

		DoSyscall(CG_R_SETCOLOR, nullptr);
	}
	void SizeText(float scalex, float scaley, const char *text, int limit, const fontInfo_t *font, float *width, float *height)
	{
		int len = strlen(text);
		if (limit > 0 && len > limit)
			len = limit;
	
		const uint8_t *s = (uint8_t*)text;

		float w = 0.0f;
		float h = 0.0f;

		for (int count = 0; *s && count < len; )
		{
			if (Q_IsColorString(s))
			{
				s += 2;
				continue;
			}

			const glyphInfo_t &glyph = font->glyphs[*s];
			w += glyph.xSkip;

			if (glyph.height > h)
				h = glyph.height;

			count++;
			s++;
		}

		*width = w * font->glyphScale * scalex;
		*height = h * font->glyphScale * scaley;
	}
	void DrawText(float x, float y, float scalex, float scaley, const vec4_t color, const char *text, float adjust, int limit, int style, int align, const fontInfo_t *font)
	{
		float w, h;
		SizeText(scalex, scaley, text, limit, font, &w, &h);

		if (align == ITEM_ALIGN_CENTER2)
			y += h / 2.0f;
		else
			y += h;

		if (align == ITEM_ALIGN_CENTER || align == ITEM_ALIGN_CENTER2)
			x -= w / 2.0f;
		else if (align == ITEM_ALIGN_RIGHT)
			x -= w;

		scalex *= font->glyphScale;
		scaley *= font->glyphScale;

		const uint8_t *s = (uint8_t*)text;
		int len = strlen(text);

		if (limit > 0 && len > limit)
			len = limit;

		vec4_t newColor;
		Vector4Copy(color, newColor);
		DoSyscall(CG_R_SETCOLOR, color);

		for (int count = 0; *s && count < len; )
		{
			const glyphInfo_t &glyph = font->glyphs[*s];

			if (Q_IsColorString(s))
			{
				const uint8_t newColorChar = *(s + 1);

				if(newColorChar == COLOR_NULL)
					VectorCopy(color, newColor);
				else
					VectorCopy(g_color_table[ColorIndex(newColorChar)], newColor);

				DoSyscall(CG_R_SETCOLOR, newColor);

				s += 2;
				continue;
			}

			float x_adj = x + glyph.pitch*scalex;
			float y_adj = y - glyph.top*scaley;
			float w_adj = glyph.imageWidth*scalex;
			float h_adj = glyph.imageHeight*scaley;

			AdjustFrom640(&x_adj, &y_adj, &w_adj, &h_adj);

			// Draw the drop shadow first
			if (style == ITEM_TEXTSTYLE_SHADOWED || style == ITEM_TEXTSTYLE_SHADOWEDMORE)
			{
				vec4_t outlineCol = {0, 0, 0, newColor[3]};
				float ofs = style == ITEM_TEXTSTYLE_SHADOWED ? 1.0f : 2.0f;
			
				DoSyscall(CG_R_SETCOLOR, outlineCol);
				DoSyscall(CG_R_DRAWSTRETCHPIC, x_adj + ofs, y_adj + ofs, w_adj, h_adj, glyph.s, glyph.t, glyph.s2, glyph.t2, glyph.glyph);
				DoSyscall(CG_R_SETCOLOR, newColor);
			}

			DoSyscall(CG_R_DRAWSTRETCHPIC, x_adj, y_adj, w_adj, h_adj, glyph.s, glyph.t, glyph.s2, glyph.t2, glyph.glyph);

			x += (glyph.xSkip * scalex) + adjust;
			count++;
			s++;
		}

		DoSyscall(CG_R_SETCOLOR, nullptr);
	}
	void DrawBoxedText(float x, float y, float scalex, float scaley, const vec4_t textColor, const char *text, float adjust, int limit, int style, int align, const fontInfo_t *font, const vec4_t bgColor, const vec4_t boColor)
	{
		const float boxPadding = 7.0f;

		float w, h;
		SizeText(scalex, scaley, text, limit, font, &w, &h);

		float _x = x, _y = y;

		if (align == ITEM_ALIGN_CENTER2)
			_y += h / 2.0f;

		if (align == ITEM_ALIGN_CENTER || align == ITEM_ALIGN_CENTER2)
			_x -= w / 2.0f;
		else if (align == ITEM_ALIGN_RIGHT)
			_x -= w;

		DrawBoxBordered2D(_x, _y, w + boxPadding, h + boxPadding, bgColor, boColor, media.whiteShader);

		DrawText(x + boxPadding/2.0f, y + boxPadding/2.0f, scalex, scaley, textColor, text, adjust, limit, style, align, font);
	}
	void DrawIcon(float x, float y, float w, float h, const vec4_t color, qhandle_t shader)
	{
		AdjustFrom640(&x, &y, &w, &h);

		DoSyscall(CG_R_SETCOLOR, color);
		DoSyscall(CG_R_DRAWSTRETCHPIC, x - w/2.0f, y - h/2.0f, w, h, 0.0f, 0.0f, 1.0f, 1.0f, shader);
		DoSyscall(CG_R_SETCOLOR, nullptr);
	}

	void DrawButton(float x, float y, float w, float h, const char *text, float textScale, std::function<void()> callback, int *currentTab = nullptr, int myTab = 0)
	{
		const bool IsHovering = cgDC_cursorx >= x && cgDC_cursorx < x + w &&
								cgDC_cursory >= y && cgDC_cursory < y + h;

		const bool DoDrawHovering = IsHovering || (currentTab && *currentTab == myTab);

		const vec_t* bgColor = DoDrawHovering
			? (btnMouseL < 0 && IsHovering)
				? colorMenuBgPr
				: colorMenuBgHl
			: colorMenuBg;

		const vec_t* boColor = DoDrawHovering 
			? (btnMouseL < 0 && IsHovering)
				? colorMenuBoPr
				: colorMenuBoHl
			: colorMenuBo;

		const int flags = DoDrawHovering 
			? (btnMouseL < 0 && IsHovering)
				? ITEM_TEXTSTYLE_SHADOWEDMORE
				: ITEM_TEXTSTYLE_SHADOWED
			: 0;

		DrawBoxBordered2D(x, y, w, h, bgColor, boColor, media.whiteShader);
		DrawText(x + w/2.0f, y + h/2.0f, textScale, textScale, colorWhite, 
			text, 0.0f, 0, flags, ITEM_ALIGN_CENTER2, &media.limboFont2);

		if (IsHovering && (btnMouseL & 1))
		{
			if (currentTab)
				*currentTab = myTab;

			if (callback)
				callback();
		}
	}
	void DrawCheckbox(float x, float y, const char *text, bool *state, float scale)
	{
		const float baseTextScale = 0.14f;
		const float baseBoxSize = 9.0f;
		
		const float currentTextScale = baseTextScale * scale;
		const float currentBoxSize = baseBoxSize * scale;

		float textW, textH;
		SizeText(currentTextScale, currentTextScale, text, 0, &media.limboFont2, &textW, &textH);

		const bool IsHovering = cgDC_cursorx >= x && cgDC_cursorx < (x + currentBoxSize + 2.0f + textW) &&
								cgDC_cursory >= y && cgDC_cursory < y + currentBoxSize;
		const vec_t *color = IsHovering ? colorCheckboxHl : colorCheckbox;

		DrawBox2D(x, y, currentBoxSize, currentBoxSize, color, *state ? media.checkboxChecked : media.checkboxUnchecked);
		DrawText(x + currentBoxSize + (2.0f * scale), y + currentBoxSize/2.0f - textH/2.0f + 0.5f, currentTextScale, currentTextScale, color, text, 0.0f, 0, 0, ITEM_ALIGN_LEFT, &media.limboFont2);

		if (IsHovering && (btnMouseL & 1))
			*state ^= 1;
	}
	void DrawMenu()
	{
		btnDelete = GetAsyncKeyState(VK_DELETE);
		btnMouseL = GetAsyncKeyState(VK_LBUTTON);

		if ((btnDelete & 1) && !(DoSyscall(CG_KEY_GETCATCHER) & (KEYCATCH_CONSOLE | KEYCATCH_UI)))
		{
			showMenu = !showMenu;

			if (!showMenu)
				DoSyscall(CG_KEY_SETCATCHER, DoSyscall(CG_KEY_GETCATCHER) & ~(KEYCATCH_MESSAGE | KEYCATCH_CGAME));
		}

		if (!showMenu)
		{
			DrawBoxedText(10.0f, 10.0f, 0.16f, 0.16f, colorWhite, XorString("^1CC^7Hook^1:^9Reloaded"), 
				0.0f, 0, ITEM_TEXTSTYLE_NORMAL, ITEM_ALIGN_LEFT, &media.limboFont1, colorMenuBg, colorMenuBo);
			return;
		}

		DoSyscall(CG_KEY_SETCATCHER, DoSyscall(CG_KEY_GETCATCHER) | KEYCATCH_CGAME | KEYCATCH_MESSAGE);

		const vec4_t background = { 0.0f, 0.0f, 0.0f, 0.7f };
		DrawBox2D(0, 0, 640, 480, background, media.whiteShader);

		DrawText(320.0f, 25.0f, 0.3f, 0.3f, colorWhite, 
			XorString("^1CC^7Hook^1:^9Reloaded"), 0.0f, 0, ITEM_TEXTSTYLE_SHADOWED, ITEM_ALIGN_CENTER, &media.limboFont1);

		static int currentTab = 0;
		const float tabWidth = 55.0f * 1.5f;
		const float tabHeight = 10.0f * 1.5f;
		const float tabTextScale = 0.14f * 1.5f;
		const float tabY = 50.0f;
		const float tabGap = 5.0f;
		float currentTabX = 143.5f;

		DrawButton(currentTabX, tabY, tabWidth, tabHeight, XorString("Aimbot"), tabTextScale, nullptr, &currentTab, 0);
		currentTabX += tabWidth + tabGap;
		DrawButton(currentTabX, tabY, tabWidth, tabHeight, XorString("Visuals"), tabTextScale, nullptr, &currentTab, 1);
		currentTabX += tabWidth + tabGap;
		DrawButton(currentTabX, tabY, tabWidth, tabHeight, XorString("ESP"), tabTextScale, nullptr, &currentTab, 2);
		currentTabX += tabWidth + tabGap;
		DrawButton(currentTabX, tabY, tabWidth, tabHeight, XorString("Misc"), tabTextScale, nullptr, &currentTab, 3);

		const float contentX = 100.0f;
		const float contentY = 100.0f;
		const float checkboxScale = 1.25f;
		const float verticalSpacing = 15.0f;
		float currentY;

		switch (currentTab)
		{
			case 0: // Aimbot
				currentY = contentY;
				DrawCheckbox(contentX, currentY, XorString("Aimbot Enabled"), &cfg.aimbotEnabled, checkboxScale); currentY += verticalSpacing;
				DrawCheckbox(contentX, currentY, XorString("Sticky Aim"), &cfg.aimbotStickyAim, checkboxScale); currentY += verticalSpacing;
				DrawCheckbox(contentX, currentY, XorString("Sticky Auto-Reset"), &cfg.aimbotStickyAutoReset, checkboxScale); currentY += verticalSpacing;
				DrawCheckbox(contentX, currentY, XorString("Lock Viewangles"), &cfg.aimbotLockViewangles, checkboxScale); currentY += verticalSpacing;
				DrawCheckbox(contentX, currentY, XorString("Autoshoot"), &cfg.aimbotAutoshoot, checkboxScale); currentY += verticalSpacing;
				DrawCheckbox(contentX, currentY, XorString("Autocrouch"), &cfg.aimbotAutoCrouch, checkboxScale); currentY += verticalSpacing;
				DrawCheckbox(contentX, currentY, XorString("Velocity Prediction"), &cfg.aimbotVelocityPrediction, checkboxScale); currentY += verticalSpacing;
				DrawCheckbox(contentX, currentY, XorString("Ping Prediction"), &cfg.aimbotPingPrediction, checkboxScale); currentY += verticalSpacing;
				DrawCheckbox(contentX, currentY, XorString("Human Aim"), &cfg.aimbotHumanAim, checkboxScale);
				break;
			case 1: // Visuals
				{
					const float column2X = contentX + 180.0f;
					const float column3X = contentX + 370.0f;
					const float indent2X = column2X + 15.0f;
					const float indent3X = column3X + 15.0f;

					float currentY_col1 = contentY;
					float currentY_col2 = contentY;
					float currentY_col3 = contentY;

					// Left column
					DrawCheckbox(contentX, currentY_col1, XorString("No Scope-FoV"), &cfg.noScopeFov, checkboxScale); currentY_col1 += verticalSpacing;
					DrawCheckbox(contentX, currentY_col1, XorString("No Scope-Blackout"), &cfg.noScopeBlackout, checkboxScale); currentY_col1 += verticalSpacing;
					DrawCheckbox(contentX, currentY_col1, XorString("Bullet Tracers"), &cfg.bulletTracers, checkboxScale); currentY_col1 += verticalSpacing;
					DrawCheckbox(contentX, currentY_col1, XorString("Grenade Trajectory"), &cfg.grenadeTrajectory, checkboxScale); currentY_col1 += verticalSpacing;
					DrawCheckbox(contentX, currentY_col1, XorString("No Damage Feedback"), &cfg.noDamageFeedback, checkboxScale); currentY_col1 += verticalSpacing;
					DrawCheckbox(contentX, currentY_col1, XorString("No Camera Shake"), &cfg.noCamExplosionShake, checkboxScale); currentY_col1 += verticalSpacing;
					DrawCheckbox(contentX, currentY_col1, XorString("No Smoke"), &cfg.noSmoke, checkboxScale); currentY_col1 += verticalSpacing;
					DrawCheckbox(contentX, currentY_col1, XorString("No Foliage"), &cfg.noFoliage, checkboxScale); currentY_col1 += verticalSpacing;
					DrawCheckbox(contentX, currentY_col1, XorString("No Weather"), &cfg.noWeather, checkboxScale); currentY_col1 += verticalSpacing;
					DrawCheckbox(contentX, currentY_col1, XorString("Missile Chams"), &cfg.missileChams, checkboxScale); currentY_col1 += verticalSpacing;

					// Middle column
					DrawCheckbox(column2X, currentY_col2, XorString("Master Wallhack"), &cfg.wallhack, checkboxScale); currentY_col2 += verticalSpacing * 1.5f;

					DrawCheckbox(column2X, currentY_col2, XorString("Player Chams"), &cfg.playerChams, checkboxScale); currentY_col2 += verticalSpacing;
					DrawCheckbox(indent2X, currentY_col2, XorString("Corpse Chams"), &cfg.playerCorpseChams, checkboxScale); currentY_col2 += verticalSpacing;
					DrawCheckbox(indent2X, currentY_col2, XorString("Team Fill Wallhack"), &cfg.teamShader1Wallhack, checkboxScale); currentY_col2 += verticalSpacing;
					DrawCheckbox(indent2X, currentY_col2, XorString("Team Outline Wallhack"), &cfg.teamShader2Wallhack, checkboxScale); currentY_col2 += verticalSpacing;
					DrawCheckbox(indent2X, currentY_col2, XorString("Enemy Fill Wallhack"), &cfg.enemyShader1Wallhack, checkboxScale); currentY_col2 += verticalSpacing;
					DrawCheckbox(indent2X, currentY_col2, XorString("Enemy Outline Wallhack"), &cfg.enemyShader2Wallhack, checkboxScale); currentY_col2 += verticalSpacing * 1.5f;

					DrawCheckbox(column2X, currentY_col2, XorString("Held Weapon Chams"), &cfg.heldWeaponChams, checkboxScale); currentY_col2 += verticalSpacing;
					DrawCheckbox(indent2X, currentY_col2, XorString("Fill Wallhack"), &cfg.weaponChamsShader1Wallhack, checkboxScale); currentY_col2 += verticalSpacing;
					DrawCheckbox(indent2X, currentY_col2, XorString("Outline Wallhack"), &cfg.weaponChamsShader2Wallhack, checkboxScale); currentY_col2 += verticalSpacing * 1.5f;

					// Right column
					DrawCheckbox(column3X, currentY_col3, XorString("Pickup Chams"), &cfg.pickupChams, checkboxScale); currentY_col3 += verticalSpacing;
					DrawCheckbox(indent3X, currentY_col3, XorString("Fill Wallhack"), &cfg.pickupChamsFillWallhack, checkboxScale); currentY_col3 += verticalSpacing;
					DrawCheckbox(indent3X, currentY_col3, XorString("Outline"), &cfg.pickupChamsOutline, checkboxScale); currentY_col3 += verticalSpacing;
					DrawCheckbox(indent3X, currentY_col3, XorString("Outline Wallhack"), &cfg.pickupChamsOutlineWallhack, checkboxScale); currentY_col3 += verticalSpacing * 1.5f;

					DrawCheckbox(column3X, currentY_col3, XorString("Dropped Wep Chams"), &cfg.droppedWeaponChams, checkboxScale); currentY_col3 += verticalSpacing;
					DrawCheckbox(indent3X, currentY_col3, XorString("Fill Wallhack"), &cfg.droppedWeaponChamsFillWallhack, checkboxScale); currentY_col3 += verticalSpacing;
					DrawCheckbox(indent3X, currentY_col3, XorString("Outline"), &cfg.droppedWeaponChamsOutline, checkboxScale); currentY_col3 += verticalSpacing;
					DrawCheckbox(indent3X, currentY_col3, XorString("Outline Wallhack"), &cfg.droppedWeaponChamsOutlineWallhack, checkboxScale);
				}
				break;
			case 2: // ESP
				currentY = contentY;
				DrawCheckbox(contentX, currentY, XorString("Head BBox"), &cfg.headBbox, checkboxScale); currentY += verticalSpacing;
				DrawCheckbox(contentX, currentY, XorString("Body BBox"), &cfg.bodyBbox, checkboxScale); currentY += verticalSpacing;
				DrawCheckbox(contentX, currentY, XorString("Bone ESP"), &cfg.boneEsp, checkboxScale); currentY += verticalSpacing;
				DrawCheckbox(contentX, currentY, XorString("Name ESP"), &cfg.nameEsp, checkboxScale); currentY += verticalSpacing;
				DrawCheckbox(contentX, currentY, XorString("Missile ESP"), &cfg.missileEsp, checkboxScale); currentY += verticalSpacing;
				DrawCheckbox(contentX, currentY, XorString("Missile Radius"), &cfg.missileRadius, checkboxScale); currentY += verticalSpacing;
				DrawCheckbox(contentX, currentY, XorString("Pickup ESP"), &cfg.pickupEsp, checkboxScale);
				break;
			case 3: // Misc
				currentY = contentY;
				DrawCheckbox(contentX, currentY, XorString("Spectator Warning"), &cfg.spectatorWarning, checkboxScale); currentY += verticalSpacing;
				DrawCheckbox(contentX, currentY, XorString("Enemy Spawntimer"), &cfg.enemySpawnTimer, checkboxScale); currentY += verticalSpacing;
				DrawCheckbox(contentX, currentY, XorString("Custom Damage Sounds"), &cfg.customDmgSounds, checkboxScale); currentY += verticalSpacing;
				DrawCheckbox(contentX, currentY, XorString("Quick Unban-Reconnect (F10)"), &cfg.quickUnbanReconnect, checkboxScale); currentY += verticalSpacing;
				DrawCheckbox(contentX, currentY, XorString("Clean Screenshots"), &cfg.cleanScreenshots, checkboxScale); currentY += verticalSpacing;
				DrawCheckbox(contentX, currentY, XorString("CVAR Unlocker (Caution)"), &cfg.cvarUnlocker, checkboxScale); currentY += verticalSpacing;
				DrawCheckbox(contentX, currentY, XorString("PicMip Hack (Visible on Screenshots)"), &cfg.picmipHack, checkboxScale); currentY += verticalSpacing;
				DrawCheckbox(contentX, currentY, XorString("Bunny Hop"), &cfg.bunnyHop, checkboxScale);
				break;
		}

		ui::DrawBox2D(cgDC_cursorx, cgDC_cursory, 32, 32, colorWhite, media.cursorIcon);
	}
}