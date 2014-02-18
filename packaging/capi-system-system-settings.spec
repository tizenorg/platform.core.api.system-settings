%bcond_with x
%bcond_with wayland

Name:       capi-system-system-settings
Summary:    A System Settings library in Tizen Native API
Version:    0.0.2
Release:    0
Group:      System/API
License:    Apache-2.0
Source0:    %{name}-%{version}.tar.gz
Source1001: %{name}.manifest
Source1002: %{name}-devel.manifest
BuildRequires:  cmake
BuildRequires:  pkgconfig(dlog)
BuildRequires:  pkgconfig(vconf)
BuildRequires:  pkgconfig(capi-base-common)
BuildRequires:  pkgconfig(elementary)
BuildRequires:  pkgconfig(ecore)
%if %{with x}
BuildRequires: pkgconfig(ecore-x)
%endif
%if %{with wayland}
BuildRequires: pkgconfig(ecore-wayland)
%endif
BuildRequires:  pkgconfig(ecore-file)
BuildRequires:  pkgconfig(appcore-efl)
BuildRequires:  pkgconfig(capi-base-common)
BuildRequires:  pkgconfig(glib-2.0)
BuildRequires:  pkgconfig(gobject-2.0)
BuildRequires:  pkgconfig(fontconfig)
BuildRequires:  pkgconfig(libxml-2.0)
BuildRequires:  pkgconfig(libtzplatform-config)

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
cp %{SOURCE1001} %{SOURCE1002} .


%build
MAJORVER=`echo %{version} | awk 'BEGIN {FS="."}{print $1}'`
%cmake . -DFULLVER=%{version} -DMAJORVER=${MAJORVER} \
%if %{with x}
        -DX11_SUPPORT=On \
%else
        -DX11_SUPPORT=Off \
%endif
%if %{with wayland}
        -DWAYLAND_SUPPORT=On
%else
        -DWAYLAND_SUPPORT=Off
%endif

make %{?jobs:-j%jobs}

%install
%make_install

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig


%files
%manifest %{name}.manifest
%license LICENSE.APLv2
%{_libdir}/lib*.so.*
/usr/bin/test_system_settings_gui

%files devel
%manifest %{name}-devel.manifest
%{_includedir}/system/*.h
%{_libdir}/pkgconfig/*.pc
%{_libdir}/lib*.so
