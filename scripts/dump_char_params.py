"""
Dump all text-readable params from csgo_character and csgo_weapon vmat_c files.
Also dump a full hex+ascii view of one csgo_character material to understand the KV3 text block.
"""
import struct, os, re

game_dir = r'C:\Program Files (x86)\Steam\steamapps\common\Counter-Strike Global Offensive\game'

def parse_vpk(vpk_dir_path):
    with open(vpk_dir_path, 'rb') as f:
        dir_data = f.read()
    sig, ver, tree_size = struct.unpack_from('<III', dir_data, 0)
    header_size = 28
    offset = header_size
    entries = {}
    try:
        while offset < header_size + tree_size:
            end = dir_data.index(b'\x00', offset)
            ext = dir_data[offset:end].decode()
            offset = end + 1
            if not ext: break
            while True:
                end = dir_data.index(b'\x00', offset)
                path = dir_data[offset:end].decode()
                offset = end + 1
                if not path: break
                while True:
                    end = dir_data.index(b'\x00', offset)
                    fname = dir_data[offset:end].decode()
                    offset = end + 1
                    if not fname: break
                    crc, small_size, archive_idx, entry_offset, entry_length, terminator = struct.unpack_from('<IHHIIH', dir_data, offset)
                    offset += 18
                    small_data = dir_data[offset:offset+small_size]
                    offset += small_size
                    full_path = f'{path}/{fname}.{ext}' if path != ' ' else f'{fname}.{ext}'
                    entries[full_path] = (archive_idx, entry_offset, entry_length, small_data)
    except:
        pass
    return entries

def read_entry(entries, vpk_base, name):
    if name not in entries: return None
    ai, eo, el, sd = entries[name]
    if el > 0:
        try:
            with open(vpk_base.format(ai), 'rb') as f:
                f.seek(eo)
                return f.read(el)
        except: return None
    return sd if sd else None

pak_dir = os.path.join(game_dir, 'csgo', 'pak01_dir.vpk')
entries = parse_vpk(pak_dir)
vpk_base = os.path.join(game_dir, 'csgo', 'pak01_{:03d}.vpk')

# Find a csgo_weapon material and dump its KV3 text block
weapon_mats = [k for k in entries if k.endswith('.vmat_c') and 'weapon' in k.lower() and 'materials' in k]
print(f"Found {len(weapon_mats)} weapon materials")

# Try to find one that has readable KV3 text (some vmat_c have a NTRO or DATA block with text)
for wm in weapon_mats[:5]:
    data = read_entry(entries, vpk_base, wm)
    if not data: continue
    # Look for KV3 text header
    if b'kv3 encoding:text' in data:
        print(f"\nFound KV3 text in: {wm}")
        idx = data.find(b'kv3 encoding:text')
        print(data[idx:idx+2000].decode('utf-8', errors='replace'))
        break
    # Look for readable shader params
    if b'csgo_weapon' in data or b'csgo_character' in data:
        # Find all printable strings >= 4 chars
        strings = re.findall(b'[a-zA-Z_][a-zA-Z0-9_]{3,}', data)
        params = set()
        for s in strings:
            s = s.decode()
            if s.startswith(('g_fl', 'g_v', 'g_t', 'F_', 'D_', 'g_b', 'g_n')):
                params.add(s)
        if params:
            print(f"\nParams in {wm}:")
            for p in sorted(params):
                print(f"  {p}")

# Also look for any vmat that has KV3 text format (not binary)
print("\n\nSearching for text-format KV3 vmats...")
count = 0
for k in sorted(entries.keys()):
    if not k.endswith('.vmat_c'): continue
    data = read_entry(entries, vpk_base, k)
    if not data: continue
    if b'kv3 encoding:text' in data:
        print(f"  TEXT KV3: {k}")
        count += 1
        if count >= 10: break

# Dump all unique F_ and g_ params from ALL vmat_c files
print("\n\nAll unique params across ALL vmat_c files:")
all_params = set()
for k in entries:
    if not k.endswith('.vmat_c'): continue
    data = read_entry(entries, vpk_base, k)
    if not data: continue
    strings = re.findall(b'[a-zA-Z_][a-zA-Z0-9_]{3,50}', data)
    for s in strings:
        s = s.decode('utf-8', errors='replace')
        if s.startswith(('g_fl', 'g_vC', 'g_tC', 'g_tN', 'g_tM', 'g_tA', 'F_DIS', 'F_ADD', 'F_TRA', 'F_IGN', 'F_BLE', 'F_REN', 'F_SUB', 'F_CLO')):
            all_params.add(s)

for p in sorted(all_params):
    print(f"  {p}")
