# Figma UI Implementation Status

## ✅ Completed

### Font System
- ✅ Using embedded Geist Regular font from `src/menu/fonts.hpp`
- ✅ Font sizes adjusted: 11px for username, 8px for subscription info
- ✅ All fonts loaded from memory (no file I/O)

### Window & Layout
- ✅ Borderless window (WS_POPUP style)
- ✅ Layered window for transparency support
- ✅ **FIXED: Window dragging** - Removed `WS_EX_TRANSPARENT` flag to allow mouse interaction
- ✅ Fullscreen window covering all monitors for unrestricted dragging
- ✅ DPI scaling system (1.5x scale factor)
- ✅ Proper window sizing: 1050x750 (700x500 base * 1.5)
- ✅ Corner rounding on main window (12px)
- ✅ Corner rounding on content area (8px)

### Top Bar
- ✅ Exact Figma colors: `rgba(40,40,40,0.4)` background
- ✅ Purple border bottom: `#658` (102, 85, 136)
- ✅ User profile section with avatar circle
- ✅ Username and subscription text with correct fonts
- ✅ Vertical separator line

### Navigation Tabs
- ✅ Icon placeholders (circles) with proper opacity
- ✅ Text properly centered vertically next to icons
- ✅ Correct spacing between icon and text (4px * dpi_scale)
- ✅ Selected state: `rgba(255,255,255,0.06)` background
- ✅ Text opacity: 80% selected, 40% unselected
- ✅ Icon opacity: 80% selected, 40% unselected
- ✅ All 5 tabs: Aimbot, Visuals, Skins, Misc, Config

### Content Area
- ✅ Proper background: `rgba(40,40,40,0.4)`
- ✅ Border: `rgba(40,40,40,0.6)`
- ✅ Rounded corners (8px)
- ✅ Proper padding and sizing with DPI scaling

### Colors
- ✅ Main window background: `rgba(5,5,5,0.85)`
- ✅ All Figma colors matched exactly

## ⏳ TODO

### Gaussian Blur Shader
The Figma design specifies `backdrop-blur-[25px]` which requires a post-processing shader.

**Implementation needed:**
1. Create a Gaussian blur pixel shader (HLSL)
2. Set up render target for offscreen rendering
3. Apply blur shader to background before rendering UI
4. Composite blurred background with UI

**Files to create:**
- `src/shaders/blur.hlsl` - Gaussian blur pixel shader
- `src/rendering/post_process.cpp` - Post-processing system
- `src/rendering/post_process.hpp` - Header

**Shader approach:**
```hlsl
// Two-pass Gaussian blur
// Pass 1: Horizontal blur
// Pass 2: Vertical blur
// Blur radius: 25px
```

**Integration in main.cpp:**
```cpp
// Before rendering ImGui:
1. Render scene to offscreen texture
2. Apply horizontal blur pass
3. Apply vertical blur pass
4. Render ImGui on top of blurred background
```

### Real Icons
Currently using circle placeholders. Need to:
- Extract icon images from Figma (crosshair, eye, palette, settings)
- Load as textures
- Render using `ImGui::Image()` or draw list

**Figma icon URLs (from design context):**
- Crosshair: `http://localhost:3845/assets/f25c6bb7fb720c74320ae80e2acce91a4e6e2f8d.png`
- Eye: `http://localhost:3845/assets/99803a4426214e17bf91f47582f5ec6f0b27c0d5.png`
- Palette: `http://localhost:3845/assets/d4198104c0388fae29ccb708f0455045623cf9a9.png`
- Settings: `http://localhost:3845/assets/04dada90c28d6632a120905c17f79051647ae8b2.png`

## Current State

The UI now:
- ✅ Matches Figma sizing and layout
- ✅ Has proper DPI scaling
- ✅ Uses Geist font correctly
- ✅ Has rounded corners
- ✅ Text is properly centered in tabs
- ✅ All colors match Figma exactly
- ❌ Missing backdrop blur effect
- ❌ Using placeholder icons instead of real ones

## Testing

Run with: `xmake run`

The window should appear as a standalone borderless window with:
- Proper sizing (1050x750)
- Rounded corners
- Correct font sizes
- Centered tab text with icon placeholders
- All Figma colors

## Next Steps

1. **Implement Gaussian blur shader** (highest priority for visual fidelity)
2. **Load real icons** from Figma assets
3. **Fine-tune DPI scaling** if needed for different displays
4. **Add actual UI content** to the tab panels
