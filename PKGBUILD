pkgname="ssh_system_finder"
pkgver="1.0.0"
pkgrel="1.0"
pkgdesc="Scan an IP or local network and identify systems that have SSH enabled."
arch=('any')
url="https://github.com/basemax/sshfinderc"
license=('GPL3')
depends=('gcc' 'make')
makedepends=('git')
maintainer=("Maximilian Edison <maximilianedison@gmail.com>"
            "Base Max <basemaxcode@gmail.com")
source=("git+$url.git")
md5sums=('SKIP')


package() {
    cd "$srcdir/sshfinderc"
    make 
    sudo install -Dm755 "$srcdir/sshfinderc/ssh_system_finder" "/usr/local/bin/ssh_system_finder"
}
