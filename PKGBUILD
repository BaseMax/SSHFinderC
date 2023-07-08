# Maintainers of the package
pkgname=ssh_system_finder
pkgver=1.0
pkgrel=1
pkgdesc="Scan an IP range or local network and identify systems that have SSH enabled"
arch=('any')
url="https://github.com/basemax/sshfinderc"
license=('GPL3')
depends=('gcc' 'make')

maintainer=("Maximilian Edison <maximilianedison@gmail.com>"
            "Max Base <basemaxcode@gmail.com>")

source=("$pkgname-$pkgver.tar.gz:https://github.com/BaseMax/SSHFinderC/releases/download/v1.0/v1.0.tar.gz")


build() {
    cd "$srcdir/sshfinderc-$pkgver"
    make
}

package() {
    cd "$srcdir/sshfinderc-$pkgver"
    make DESTDIR="$pkgdir" install
}
