Summary: A game of 5-element shapes
Name: pentamino
Version: 0.1.1
Release: 1
Copyright: GPL
Group: Amusements/Games
URL: http://www.livejournal.com/~kolen/
Packager: kolen
Source: %{name}-%{version}.tar.gz
BuildRoot: %{_tmppath}/%{name}-%{version}-root
BuildPrereq: SDL-devel

%description
A game of 5-element shapes that you can move, rotate and turn.
Stupid hack - 2.

%prep
%setup

%build
./configure --prefix=/usr
make

%install
rm -rf $RPM_BUILD_ROOT
make prefix=$RPM_BUILD_ROOT/usr sysconfdir=$RPM_BUILD_ROOT/etc install

find $RPM_BUILD_ROOT/usr/ -type f -print | \
    grep -v '\/(README|COPYING|INSTALL|TODO|ChangeLog)$' | \
    sed "s@^$RPM_BUILD_ROOT@@g" | \
    sed 's/^\(.\+\/man.\+\)$/\1*/g' \
    > %{name}-%{version}-filelist
    
%clean
rm -rf $RPM_BUILD_ROOT

%files -f %{name}-%{version}-filelist
%defattr(-, root, root)

#%doc README COPYING ChangeLog

%changelog
