Summary: a graphical benchmark software
Name: hdbench
Version: 0.14.1
Release: 1
Source: http://www.enjoy.ne.jp/~gm/program/hdbench/arc/hdbench-0.14.1.tar.gz
Copyright: GPL
Group: X11/Applications
Packager: Yuuki NINOMIYA <gm@smn.enjoy.ne.jp>
URL: http://www.enjoy.ne.jp/~gm/
Buildroot: /tmp/rpm-hdbench
Summary(ja): グラフィカルベンチマークソフトウェア

%description
HDBENCH clone is a graphical benchmark software like HDBENCH
which is the most famous benchmark software for Windows in Japan.
It measures the performance of CPU (integer, floating point),
video (rectangle, circle, text, scroll, image) and disk (read, write).

%description -l ja
HDBENCH clone は日本で最も有名な Windows 用ベンチマークソフトである
HDBENCH にそっくりのソフトです。
このソフトであなたの PC の、CPU (整数演算, 浮動小数点演算)、
VIDEO (矩形, 円, テキスト, スクロール, IMAGE)、
DISK (読み込み, 書き込み) のパフォーマンスを計測することができます。

%changelog
* Tue Nov 30 1999 Yuuki NINOMIYA <gm@smn.enjoy.ne.jp>
- for version 0.14.1

* Wed Oct 06 1999 Yuuki NINOMIYA <gm@smn.enjoy.ne.jp>
- for version 0.14.0

* Mon Sep 27 1999 Yuuki NINOMIYA <gm@smn.enjoy.ne.jp>
- for version 0.13.1

* Fri Sep 10 1999 Yuuki NINOMIYA <gm@smn.enjoy.ne.jp>
- 1st release for version 0.13.0

%prep

%setup

%build
./configure --prefix=/usr
make

%install
make prefix=$RPM_BUILD_ROOT/usr install-strip

%clean
rm -rf $RPM_BUILD_ROOT

%files
%defattr(-,root,root)
%doc doc/ChangeLog.jp
%doc doc/COPYING
%doc doc/COPYING.jp
%doc doc/README.jp
%doc doc/RESULTS.html
%doc doc/ALGORITHM.jp
%doc doc/RESULTS
%doc doc/sample.gtkrc
%doc doc/BUGS.jp
%doc doc/FAQ.jp
%doc doc/TODO.jp
%doc doc/AUTHORS
%doc doc/BUGS
%doc doc/ChangeLog
%doc doc/FAQ
%doc doc/README
%doc doc/TODO
%doc doc/WANTED
%doc doc/WANTED.jp
%doc doc/THANKS

/usr/share/locale/ja/LC_MESSAGES/hdbench.mo
/usr/share/hdbench/pixmaps/cpu.xpm
/usr/share/hdbench/pixmaps/disk.xpm
/usr/share/hdbench/pixmaps/video.xpm
/usr/bin/hdbench

