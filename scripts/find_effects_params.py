import struct, os

game_dir = r'C:\Program Files (x86)\Steam\steamapps\common\Counter-Strike Global Offensive\game'

def parse_vpk(vpk_dir_path, vpk_data_base):
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
    return entries, vpk_data_base

def read_entry(entries, vpk_data_base, name):
    if name not in entries: return None
    archive_idx, entry_offset, entry_length, small_data = entries[name]
    if entry_length > 0:
        try:
            with open(vpk_data_base.format(archive_idx), 'rb') as f:
                f.seek(entry_offset)
                return f.read(min(entry_length, 8000))
        except: return None
    return small_data if small_data else None

def extract_strings(content):
    i = 0
    current = b''
    results = []
    while i < len(content):
        b = content[i]
        if b >= 32 and b < 127:
            current += bytes([b])
        else:
            if len(current) >= 3:
                results.append(current.decode('utf-8', errors='replace'))
            current = b''
        i += 1
    return results

pak_dir = os.path.join(game_dir, 'csgo', 'pak01_dir.vpk')
entries, vpk_base = parse_vpk(pak_dir, os.path.join(game_dir, 'csgo', 'pak01_{:03d}.vpk'))

# Collect ALL unique parameter names from csgo_effects materials
all_params = set()
count = 0
for vmat in sorted(entries.keys()):
    if not vmat.endswith('.vmat_c'): continue
    content = read_entry(entries, vpk_base, vmat)
    if not content or b'csgo_effects' not in content: continue
    
    strings = extract_strings(content)
    for s in strings:
        if s.startswith('g_fl') or s.startswith('g_v') or s.startswith('g_t') or s.startswith('F_') or s.startswith('D_'):
            all_params.add(s)
    count += 1

print(f'Found {count} csgo_effects materials')
print(f'\nAll unique parameters:')
for p in sorted(all_params):
    print(f'  {p}')
