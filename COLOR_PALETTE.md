# Color Palette Reference

## Current Color Scheme

### Accent Colors (Purple)
```
Primary Accent:   RGB(139, 92, 246)  - #8B5CF6 - Purple-500
Hover Accent:     RGB(124, 58, 237)  - #7C3AED - Purple-600
Active Accent:    RGB(109, 40, 217)  - #6D28D9 - Purple-700
```

### Background Colors
```
Main Window:      RGB(11, 11, 15)    - #0B0B0F - Darkest
Child Window:     RGB(14, 14, 18)    - #0E0E12 - Very Dark
Group Box:        RGB(17, 17, 22)    - #111116 - Dark Elevated
Frame/Button:     RGB(20, 20, 26)    - #14141A - Slightly Elevated
Frame Hover:      RGB(25, 25, 31)    - #19191F - Hover State
Frame Active:     RGB(30, 30, 36)    - #1E1E24 - Active State
```

### Border Colors
```
Subtle Border:    RGB(30, 30, 36)    - #1E1E24 - Low opacity (60%)
```

### Text Colors
```
Primary Text:     RGB(240, 242, 245) - #F0F2F5 - Bright White
Disabled Text:    RGB(110, 118, 130) - #6E7682 - Muted Gray
```

### Scrollbar Colors
```
Scrollbar BG:     RGB(14, 14, 18)    - #0E0E12 - Transparent
Scrollbar Grab:   RGB(50, 50, 60)    - #32323C - Subtle
Grab Hover:       RGB(60, 60, 70)    - #3C3C46 - Slightly Brighter
Grab Active:      RGB(70, 70, 80)    - #464650 - Active State
```

## Design Principles

### Hierarchy
1. **Darkest** - Main window background (11, 11, 15)
2. **Very Dark** - Child windows and popups (14, 14, 18)
3. **Dark Elevated** - Group boxes and containers (17, 17, 22)
4. **Slightly Elevated** - Interactive elements (20, 20, 26)
5. **Hover** - Hover states (25, 25, 31)
6. **Active** - Active/pressed states (30, 30, 36)

### Contrast
- Background to text: High contrast for readability
- Element separation: Subtle elevation through slight color differences
- Borders: Very subtle, low opacity for clean look

### Accent Usage
- Selected states (tabs, checkboxes)
- Interactive feedback (hover, active)
- Visual indicators (underlines, side bars)
- Focus states

## Comparison with Common Themes

### Similar to:
- **Discord Dark**: Similar dark grays with purple accents
- **VS Code Dark+**: Similar background hierarchy
- **Tailwind Dark**: Using Tailwind purple-500/600/700 for accents

### Differences:
- Darker than most themes for premium feel
- More subtle borders and separators
- Higher text contrast for gaming environment
- Purple accent instead of blue for modern look

## Customization Guide

To change the accent color, modify in `src/menu/ui/ui.hpp`:

```cpp
// Current (Purple)
inline int accent[4] = { 139, 92, 246, 255 };
inline int accent_hover[4] = { 124, 58, 237, 255 };
inline int accent_active[4] = { 109, 40, 217, 255 };

// Alternative: Blue
inline int accent[4] = { 59, 130, 246, 255 };        // #3B82F6
inline int accent_hover[4] = { 37, 99, 235, 255 };   // #2563EB
inline int accent_active[4] = { 29, 78, 216, 255 };  // #1D4ED8

// Alternative: Green
inline int accent[4] = { 34, 197, 94, 255 };         // #22C55E
inline int accent_hover[4] = { 22, 163, 74, 255 };   // #16A34A
inline int accent_active[4] = { 21, 128, 61, 255 };  // #15803D

// Alternative: Red
inline int accent[4] = { 239, 68, 68, 255 };         // #EF4444
inline int accent_hover[4] = { 220, 38, 38, 255 };   // #DC2626
inline int accent_active[4] = { 185, 28, 28, 255 };  // #B91C1C

// Alternative: Cyan
inline int accent[4] = { 6, 182, 212, 255 };         // #06B6D4
inline int accent_hover[4] = { 8, 145, 178, 255 };   // #0891B2
inline int accent_active[4] = { 14, 116, 144, 255 }; // #0E7490
```

## Accessibility Notes

- **Contrast Ratio**: Text to background exceeds WCAG AA standards
- **Color Blindness**: Accent color is distinguishable by brightness
- **Low Vision**: High contrast mode compatible
- **Focus Indicators**: Clear visual feedback on all interactive elements

## Export for Design Tools

### Figma/Sketch Variables
```
--bg-darkest: #0B0B0F
--bg-very-dark: #0E0E12
--bg-dark: #111116
--bg-elevated: #14141A
--bg-hover: #19191F
--bg-active: #1E1E24

--accent-primary: #8B5CF6
--accent-hover: #7C3AED
--accent-active: #6D28D9

--text-primary: #F0F2F5
--text-disabled: #6E7682

--border-subtle: #1E1E24
```

### CSS Variables
```css
:root {
  --bg-darkest: rgb(11, 11, 15);
  --bg-very-dark: rgb(14, 14, 18);
  --bg-dark: rgb(17, 17, 22);
  --bg-elevated: rgb(20, 20, 26);
  --bg-hover: rgb(25, 25, 31);
  --bg-active: rgb(30, 30, 36);
  
  --accent-primary: rgb(139, 92, 246);
  --accent-hover: rgb(124, 58, 237);
  --accent-active: rgb(109, 40, 217);
  
  --text-primary: rgb(240, 242, 245);
  --text-disabled: rgb(110, 118, 130);
  
  --border-subtle: rgba(30, 30, 36, 0.6);
}
```
