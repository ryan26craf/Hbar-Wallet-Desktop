# Installation Guide - HBAR Wallet Desktop

## 🎯 Quick Start (Windows Users)

### Download from Releases

**The easiest way to get HBAR Wallet Desktop:**

1. **Visit the Releases page**: [https://github.com/yourusername/hbar-wallet-desktop/releases](https://github.com/yourusername/hbar-wallet-desktop/releases)

2. **Download the latest version**:
   - Look for `HbarWalletDesktop-vX.X.X-Windows.zip`
   - Click to download

3. **Extract the ZIP file**:
   - Right-click the downloaded file
   - Select "Extract All..."
   - Choose a location (e.g., `C:\Program Files\HbarWallet\`)

4. **Run the wallet**:
   - Navigate to the extracted folder
   - Double-click `HbarWalletDesktop.exe`
   - Windows may show a security warning - click "More info" then "Run anyway"

5. **First launch**:
   - Create a new wallet or restore from mnemonic
   - Set a strong password
   - **SAVE YOUR RECOVERY PHRASE!**

### ⚠️ Security Warning

- **ONLY download from the official GitHub Releases page**
- Verify the checksum (SHA256 hash provided in releases)
- Never run executables from unknown sources

## 📋 System Requirements

### Windows
- **OS**: Windows 10 (64-bit) or later
- **RAM**: 4 GB minimum, 8 GB recommended
- **Disk Space**: 100 MB free
- **Internet**: Required for transactions

### Optional Requirements
- Antivirus: May need to whitelist the application
- Firewall: Allow network access for the app

## 🔧 Building from Source (Advanced)

### Prerequisites

1. **Install Visual Studio 2022**:
   - Download from: https://visualstudio.microsoft.com/
   - Select "Desktop development with C++"
   - Include CMake tools

2. **Install Qt 6**:
   - Download from: https://www.qt.io/download
   - Install Qt 6.5 or later
   - Select MSVC 2022 64-bit component

3. **Install OpenSSL**:
   ```powershell
   # Using vcpkg (recommended)
   git clone https://github.com/Microsoft/vcpkg.git
   cd vcpkg
   .\bootstrap-vcpkg.bat
   .\vcpkg install openssl:x64-windows
   ```

4. **Install CMake**:
   - Download from: https://cmake.org/download/
   - Or install via Visual Studio

### Build Steps

1. **Clone the repository**:
   ```powershell
   git clone https://github.com/yourusername/hbar-wallet-desktop.git
   cd hbar-wallet-desktop
   ```

2. **Set Qt path** (if not in PATH):
   ```powershell
   $env:CMAKE_PREFIX_PATH = "C:\Qt\6.5.0\msvc2022_64"
   ```

3. **Run build script**:
   ```powershell
   .\scripts\build-windows.bat
   ```

   Or manually:
   ```powershell
   mkdir build
   cd build
   cmake .. -G "Visual Studio 17 2022" -A x64
   cmake --build . --config Release
   ```

4. **Find the executable**:
   - Location: `build\bin\Release\HbarWalletDesktop.exe`

5. **Deploy Qt dependencies**:
   ```powershell
   cd build\bin\Release
   windeployqt HbarWalletDesktop.exe
   ```

## 🐧 Linux Installation

### From Package (Coming Soon)

Ubuntu/Debian:
```bash
sudo add-apt-repository ppa:hbarwallet/ppa
sudo apt update
sudo apt install hbar-wallet-desktop
```

### Build from Source

```bash
# Install dependencies
sudo apt install build-essential cmake qt6-base-dev libssl-dev

# Clone and build
git clone https://github.com/yourusername/hbar-wallet-desktop.git
cd hbar-wallet-desktop
mkdir build && cd build
cmake ..
make -j$(nproc)
sudo make install
```

## 🍎 macOS Installation (Coming Soon)

```bash
# Via Homebrew (when available)
brew install hbar-wallet-desktop

# Or build from source
git clone https://github.com/yourusername/hbar-wallet-desktop.git
cd hbar-wallet-desktop
mkdir build && cd build
cmake ..
make -j$(sysctl -n hw.ncpu)
```

## ✅ Verification

### Check Installation

After installation, verify:

1. **Application starts**: Launch the executable
2. **Create wallet**: Test wallet creation
3. **View account**: Check if account is displayed
4. **Network connection**: Status bar should show "Connected"

### Verify Download Integrity

Always verify the SHA256 checksum:

Windows PowerShell:
```powershell
Get-FileHash .\HbarWalletDesktop-vX.X.X-Windows.zip -Algorithm SHA256
```

Compare with the hash published in the release notes.

## 🔐 First Time Setup

1. **Launch application**
2. **Choose**:
   - "Create New Wallet" for first-time users
   - "Restore Wallet" if you have a recovery phrase

3. **Set password**:
   - Minimum 8 characters
   - Use mix of letters, numbers, symbols
   - Don't forget it - it cannot be recovered!

4. **Save recovery phrase**:
   - Write down all 24 words
   - Store in safe place (not on computer!)
   - Never share with anyone
   - This is THE ONLY way to recover your wallet

5. **Verify phrase**:
   - Re-enter words to confirm
   - Check for typos

6. **Your wallet is ready!**
   - Account ID displayed
   - Can now receive HBAR

## 🆘 Troubleshooting

### "Windows protected your PC" warning

This is normal for new applications:
1. Click "More info"
2. Click "Run anyway"
3. Consider adding to antivirus whitelist

### Missing DLL errors

If you see errors about missing DLLs:
- Install Visual C++ Redistributable 2022
- Download from: https://aka.ms/vs/17/release/vc_redist.x64.exe

### Application won't start

1. Check system requirements
2. Update Windows
3. Install missing dependencies
4. Check antivirus logs
5. Run as administrator

### Can't connect to network

1. Check internet connection
2. Check firewall settings
3. Try different network (testnet/mainnet)
4. Check Hedera network status

## 📞 Get Help

- **GitHub Issues**: Report bugs or ask questions
- **Discord**: Join our community server
- **Email**: support@hbarwallet.com
- **Documentation**: Full docs at docs.hbarwallet.com

## 🔄 Updating

### Windows

1. Download new version from Releases
2. Close old version
3. Extract new version
4. Run new executable
5. Your wallet data is preserved

**Wallet files are separate from the application**, so updates won't affect your accounts.

## 🗑️ Uninstalling

### Windows

1. Close the application
2. Delete the application folder
3. (Optional) Delete wallet data:
   - Location: `%APPDATA%\HbarWallet\`
   - **WARNING**: Only delete if you have backup of recovery phrase!

---

## ⚠️ Important Reminders

✅ **ALWAYS download from official GitHub Releases**  
✅ **Verify file checksums**  
✅ **Save recovery phrase offline**  
✅ **Never share private keys**  
✅ **Test with small amounts first**  

**Need the latest version?** → [Go to Releases](https://github.com/yourusername/hbar-wallet-desktop/releases)
