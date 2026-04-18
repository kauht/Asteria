import struct, os

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

pak_dir = os.path.join(game_dir, 'csgo', 'pak01_dir.vpk')
entries = parse_vpk(pak_dir)
vpk_base = os.path.join(game_dir, 'csgo', 'pak01_{:03d}.vpk')

# Find all unique shaders used in vmat_c files
shaders = {}
for k in entries:
    if not k.endswith('.vmat_c'):
        continue
    ai, eo, el, sd = entries[k]
    if el > 0:
        try:
            with open(vpk_base.format(ai), 'rb') as f:
                f.seek(eo)
                data = f.read(min(el, 2000))
        except:
            continue
    else:
        data = sd
    # extract shader name - look for .vfx string
    idx = data.find(b'.vfx')
    if idx != -1:
        start = idx
        while start > 0 and data[start-1:start] not in (b'"', b'\x00', b' '):
            start -= 1
        shader = data[start:idx+4].decode('utf-8', errors='replace').strip('"')
        shaders[shader] = shaders.get(shader, 0) + 1

print("All shaders found in vmat_c files:")
for s, c in sorted(shaders.items(), key=lambda x: -x[1]):
    print(f'  {c:4d}  {s}')

# Also dump all params from csgo_character materials
print("\n\nAll params in csgo_character.vfx materials:")
char_params = set()
for k in entries:
    if not k.endswith('.vmat_c'):
        continue
    ai, eo, el, sd = entries[k]
    if el > 0:
        try:
            with open(vpk_base.format(ai), 'rb') as f:
                f.seek(eo)
                data = f.read(min(el, 4000))
        except:
            continue
    else:
        data = sd
    if b'csgo_character' not in data:
        continue
    # extract all param-like strings
    i = 0
    cur = b''
    while i < len(data):
        b = data[i:i+1]
        if b[0] >= 32 and b[0] < 127:
            cur += b
        else:
            s = cur.decode('utf-8', errors='replace')
            if (s.startswith('g_fl') or s.startswith('g_v') or s.startswith('g_t') or
                s.startswith('F_') or s.startswith('D_') or s.startswith('g_b')):
                char_params.add(s)
            cur = b''
        i += 1
for p in sorted(char_params):
    print(f'  {p}')
