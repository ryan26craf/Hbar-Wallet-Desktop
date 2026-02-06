# HBAR Wallet Desktop
![hbar](https://github.com/user-attachments/assets/6138233f-87e7-48e3-a8b0-803848a103d5)

A secure, open-source desktop wallet for Hedera (HBAR) cryptocurrency built with C++ and Qt6.

![Platform](https://img.shields.io/badge/platform-Windows-blue)
![License](https://img.shields.io/badge/license-MIT-green)
![Version](https://img.shields.io/badge/version-1.0.0-orange)

## ⚠️ Installation Instructions

### Download the Latest Release

**To install HBAR Wallet Desktop, please visit the Releases page:**

👉 **[Go to Releases](https://github.com/yourusername/hbar-wallet-desktop/releases)** 👈

1. Navigate to the [Releases page](https://github.com/yourusername/hbar-wallet-desktop/releases)
2. Download the latest `HbarWalletDesktop-1.0.0-Windows.zip`
3. Extract the ZIP file
4. Run `HbarWalletDesktop.exe`

**DO NOT** download files from any other source!

## Features

✅ **Secure Key Management** - Your private keys never leave your device  
✅ **HD Wallet Support** - BIP39/BIP44 mnemonic phrases  
✅ **Multiple Accounts** - Manage multiple HBAR accounts  
✅ **Transaction History** - Track all your transactions  
✅ **Password Protection** - Encrypted wallet storage  
✅ **Network Selection** - Mainnet, Testnet, and Previewnet support  
✅ **Clean UI** - Modern, user-friendly interface  
✅ **Cross-Platform Ready** - Currently Windows, Linux/Mac coming soon

## System Requirements

### Windows
- Windows 10 or later (64-bit)
- 4 GB RAM minimum
- 100 MB free disk space
- Internet connection

## Quick Start

### First Time Setup

1. **Download** the latest release from the [Releases page](https://github.com/yourusername/hbar-wallet-desktop/releases)
2. **Extract** the ZIP file to a folder
3. **Run** `HbarWalletDesktop.exe`
4. **Create** a new wallet or restore from mnemonic
5. **Save** your recovery phrase securely (write it down!)

### Creating a Wallet

1. Click "File" → "Create Wallet"
2. Enter a strong password (minimum 8 characters)
3. **IMPORTANT:** Write down your 24-word recovery phrase
4. Store it in a safe place (not on your computer!)
5. Confirm your recovery phrase
6. Your wallet is ready!

### Restoring a Wallet

1. Click "File" → "Create Wallet"
2. Select "Restore from Mnemonic"
3. Enter your 24-word recovery phrase
4. Set a password
5. Your accounts will be restored

## Security Best Practices

🔐 **Never share your private keys or recovery phrase**  
🔐 **Always verify the download URL** (github.com/yourusername/hbar-wallet-desktop)  
🔐 **Keep your recovery phrase offline** - Write it down, don't store digitally  
🔐 **Use a strong password** - At least 12 characters with mixed case, numbers, symbols  
🔐 **Backup your wallet file** - Store encrypted backup in multiple secure locations  
🔐 **Verify checksums** - Check SHA256 hash of downloaded files  

## Building from Source

### Prerequisites

- CMake 3.20 or higher
- C++17 compatible compiler (MSVC 2019+, GCC 9+, Clang 10+)
- Qt 6.5 or higher
- OpenSSL 3.0 or higher
- Git

### Windows Build Instructions

```powershell
# Install dependencies via vcpkg
vcpkg install qt6 openssl

# Clone repository
git clone https://github.com/yourusername/hbar-wallet-desktop.git
cd hbar-wallet-desktop

# Create build directory
mkdir build
cd build

# Configure
cmake .. -DCMAKE_TOOLCHAIN_FILE=[vcpkg root]/scripts/buildsystems/vcpkg.cmake

# Build
cmake --build . --config Release

# Binary will be in build/bin/Release/HbarWalletDesktop.exe
```

### Linux Build Instructions

```bash
# Install dependencies (Ubuntu/Debian)
sudo apt install build-essential cmake qt6-base-dev libssl-dev

# Clone and build
git clone https://github.com/yourusername/hbar-wallet-desktop.git
cd hbar-wallet-desktop
mkdir build && cd build
cmake ..
make -j$(nproc)

# Binary will be in build/bin/HbarWalletDesktop
```

## Project Structure

```
hbar-wallet-desktop/
├── src/                    # Source files
│   ├── main.cpp           # Application entry point
│   ├── wallet/            # Wallet logic
│   ├── crypto/            # Cryptography
│   ├── network/           # Hedera network communication
│   ├── ui/                # Qt user interface
│   ├── storage/           # Persistent storage
│   └── utils/             # Utilities
├── include/               # Header files
├── resources/             # Icons, images, etc.
├── tests/                 # Unit tests
├── docs/                  # Documentation
├── CMakeLists.txt         # Build configuration
└── README.md              # This file
```

## Configuration

Wallet files are stored in:
- **Windows:** `%APPDATA%/HbarWallet/`
- **Linux:** `~/.config/HbarWallet/`
- **macOS:** `~/Library/Application Support/HbarWallet/`

Configuration file: `config.json`

## Troubleshooting

### Wallet won't open
- Check your password is correct
- Ensure wallet file isn't corrupted
- Try restoring from mnemonic

### Can't see balance
- Check internet connection
- Verify you're on correct network (mainnet/testnet)
- Click "Refresh" button
- Check Hedera network status

### Transaction failed
- Ensure sufficient balance for fees
- Verify recipient address format
- Check network connectivity

## FAQ

**Q: Is my money safe?**  
A: Your private keys are encrypted and stored only on your device. Never share your recovery phrase.

**Q: I lost my recovery phrase, can you recover it?**  
A: No. No one can recover your wallet without the recovery phrase. Always back it up securely.

**Q: What networks are supported?**  
A: Mainnet (production), Testnet (testing), and Previewnet (preview features).

**Q: Can I import existing accounts?**  
A: Yes! Use "Import Account" and enter your private key.

**Q: Is there a mobile version?**  
A: Not yet, but it's on the roadmap!

## Roadmap

- [ ] Linux and macOS builds
- [ ] Hardware wallet support (Ledger, Trezor)
- [ ] Multi-signature accounts
- [ ] Token management (HTS tokens)
- [ ] NFT support
- [ ] Dark mode
- [ ] Address book
- [ ] Transaction templates
- [ ] Mobile apps

## Contributing

Contributions are welcome! Please read [CONTRIBUTING.md](CONTRIBUTING.md) first.

1. Fork the repository
2. Create your feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

## Security

Found a security vulnerability? **DO NOT** open a public issue.

Email: security@hbarwallet.com

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Disclaimer

⚠️ **USE AT YOUR OWN RISK**

This wallet is provided "as is" without warranty of any kind. The developers are not responsible for any loss of funds. Always:
- Test with small amounts first
- Keep backups of your recovery phrase
- Never share private keys
- Verify all transactions before confirming

## Acknowledgments

- Hedera Hashgraph team
- Qt Framework
- OpenSSL Project
- All contributors

---

Made with ❤️ by the HBAR Wallet team

**Remember: Visit [Releases](https://github.com/yourusername/hbar-wallet-desktop/releases) to download!**
