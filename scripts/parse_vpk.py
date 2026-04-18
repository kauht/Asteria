import struct

vpk_path = r'C:\Program Files (x86)\Steam\steamapps\common\Counter-Strike Global Offensive\game\csgo_core\shaders_pc_dir.vpk'

with open(vpk_path, 'rb') as f:
    data = f.read()

sig, ver, tree_size = struct.unpack_from('<III', data, 0)
print(f'Signature: 0x{sig:X}, Version: {ver}, Tree size: {tree_size}')
print(f'Total file size: {len(data)}')

# Print first 200 bytes as hex to understand structure
print('\nFirst 200 bytes:')
for i in range(0, min(200, len(data)), 16):
    hex_part = ' '.join(f'{b:02x}' for b in data[i:i+16])
    ascii_part = ''.join(chr(b) if 32 <= b < 127 else '.' for b in data[i:i+16])
    print(f'{i:04x}: {hex_part:<48} {ascii_part}')

# Print all strings found in the file
print('\nAll strings in VPK:')
i = 0
current = b''
strings = []
while i < len(data):
    b = data[i]
    if b >= 32 and b < 127:
        current += bytes([b])
    else:
        if len(current) > 3:
            strings.append((i - len(current), current.decode('utf-8', errors='replace')))
        current = b''
    i += 1

for addr, s in strings[:100]:
    print(f'  0x{addr:04x}: {s}')
