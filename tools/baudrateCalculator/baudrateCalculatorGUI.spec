# -*- mode: python ; coding: utf-8 -*-

block_cipher = None


a = Analysis(['baudrateCalculatorGUI.py'],
             pathex=['C:\\Users\\Mohammed\\Documents\\Programming\\ARM\\tools\\baudrateCalculator'],
             binaries=[],
             datas=[('images/appIcon.ico','images/')],
             hiddenimports=[],
             hookspath=[],
             runtime_hooks=[],
             excludes=[],
             win_no_prefer_redirects=False,
             win_private_assemblies=False,
             cipher=block_cipher,
             noarchive=False)
pyz = PYZ(a.pure, a.zipped_data,
             cipher=block_cipher)
exe = EXE(pyz,
          a.scripts,
          [],
          exclude_binaries=True,
          name='baudrateCalculatorGUI',
          debug=False,
          bootloader_ignore_signals=False,
          strip=False,
          upx=True,
          console=False , icon='images/appIcon.ico')
coll = COLLECT(exe,
               a.binaries,
               a.zipfiles,
               a.datas,
               strip=False,
               upx=True,
               upx_exclude=[],
               name='baudrateCalculatorGUI')
