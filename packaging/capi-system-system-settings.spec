Name:       capi-system-system-settings
Summary:    A System Settings library in Tizen Native API
Version:    0.0.2
Release:    3
Group:      System/API
License:    Apache-2.0
Source0:    %{name}-%{version}.tar.gz
BuildRequires:  cmake
BuildRequires:  pkgconfig(dlog)
BuildRequires:  pkgconfig(vconf)
BuildRequires:  pkgconfig(capi-base-common)
BuildRequires:  pkgconfig(elementary)
BuildRequires:  pkgconfig(ecore)
BuildRequires:  pkgconfig(ecore-x)
BuildRequires:  pkgconfig(ecore-file)
BuildRequires:  pkgconfig(appcore-efl)
BuildRequires:  pkgconfig(capi-base-common)
BuildRequires:  pkgconfig(glib-2.0)
BuildRequires:  pkgconfig(gobject-2.0)
BuildRequires:  pkgconfig(fontconfig)
BuildRequires:  pkgconfig(libxml-2.0)

%description
A System Settings library in Tizen Native API.


%package devel
Summary:  A System Settings library in Tizen Native API (Development)
Group:    Development/System
Requires: %{name} = %{version}-%{release}
Requires:  pkgconfig(capi-base-common)

%description devel
%devel_desc



%prep
%setup -q


%build
MAJORVER=`echo %{version} | awk 'BEGIN {FS="."}{print $1}'`
%cmake . -DFULLVER=%{version} -DMAJORVER=${MAJORVER}

make %{?jobs:-j%jobs}

%install
%make_install

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig


%files
%license LICENSE.APLv2
%manifest system-settings.manifest
%{_libdir}/lib*.so.*
/usr/bin/test_system_settings_gui

%files devel
%{_includedir}/system/*.h
%{_libdir}/pkgconfig/*.pc
%{_libdir}/lib*.so
