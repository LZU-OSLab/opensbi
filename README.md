RISC-V Open Source Supervisor Binary Interface (OpenSBI)
========================================================

The **RISC-V Supervisor Binary Interface (SBI)** is the recommended interface
between:

1. A platform specific firmware running in M-mode and bootloader, hypervisor or
   a general purpose OS executing in S-mode or HS-mode.
2. A hypervisor running in HS-mode and a bootloader or a general purpose OS
   executing in VS-mode.

The *RISC-V SBI specification* is maintained as an independent project by the
RISC-V Foundation in [Github].

The goal of the OpenSBI project is to provide an open-source reference
implementation of the RISC-V SBI specifications for platform specific firmwares
executing in M-mode (case 1 mentioned above). OpenSBI implementation can be
easily extended by RISC-V platform and system-on-chip vendors to fit a
particular hardware configuration.

The main component of OpenSBI is provided in the form of a platform independent
static library **libsbi.a** implementing the SBI interface. A firmware or
bootloader implementation can link against this library to ensure conformance
with the SBI interface specifications. *libsbi.a* also defines an interface for
integrating with platform specific operations provided by the platform firmware
implementation (e.g. console access functions, inter-processor interrupts
control, etc).

To illustrate the use of *libsbi.a* library, OpenSBI also provides a set of
platform specific support examples. For each example, a platform
specific static library *libplatsbi.a* can be compiled. This library implements
SBI calls processing by integrating *libsbi.a* with necessary platform dependent
hardware manipulation functions. For all supported platforms, OpenSBI also
provides several runtime firmware examples built using the platform
*libplatsbi.a*. These example firmwares can be used to replace the legacy
*riskv-pk* bootloader (aka BBL) and enable the use of well known bootloaders
such as [U-Boot].

Required Toolchain
------------------

OpenSBI can be compiled natively or cross-compiled on a x86 host. For
cross-compilation, you can build your tool chain or just download from
the [bootlin] (https://toolchains.bootlin.com/).

Please note that only 64bit version of toolchain is available in bootlin
for now.

Building and Installing OpenSBI Platform Independent Library
------------------------------------------------------------

OpenSBI platform independent static library *libsbi.a* can be natively compiled
or cross-compiled on a host with a different base architecture than RISC-V.

For cross-compiling, the environment variable *CROSS_COMPILE* must be defined
to specify the name prefix of the RISC-V compiler toolchain executables, e.g.
*riscv64-unknown-elf-* if the gcc executable used is *riscv64-unknown-elf-gcc*.

To build *libsbi.a* simply execute:
```
make
```

All compiled binaries as well as the result *libsbi.a* static library file will
be placed in the *build/lib* directory. To specify an alternate build root
directory path, run:
```
make O=<build_directory>
```

To generate files to be installed for using *libsbi.a* in other projects, run:
```
make install
```

This will create the *install* directory with all necessary include files
copied under the *install/include* directory and library file copied in the
*install/lib* directory. To specify an alternate installation root directory
path, run:
```
make I=<install_directory> install
```

Building and Installing a Reference Platform Static Library and Firmwares
-------------------------------------------------------------------------

When the *PLATFORM=<platform_subdir>* argument is specified on the make command
line, the platform specific static library *libplatsbi.a* and firmware examples
are built for the platform *<platform_subdir>* present in the directory
*platform* in OpenSBI top directory. For example, to compile the platform
library and firmware examples for QEMU RISC-V *virt* machine,
*<platform_subdir>* should be *qemu/virt*.

To build *libsbi.a*, *libplatsbi.a* and the firmwares for one of the supported
platform, run:
```
make PLATFORM=<platform_subdir>
```

An alternate build directory path can also be specified.
```
make PLATFORM=<platform_subdir> O=<build_directory>
```

The platform specific library *libplatsbi.a* will be generated in the
*build/platform/<platform_subdir>/lib* directory. The platform firmware files
will be under the *build/platform/<platform_subdir>/firmware* directory.
The compiled firmwares will be available in two different format: an ELF file
and an expanded image file.

To install *libsbi.a*, *libplatsbi.a*, and the compiled firmwares, run:
```
make PLATFORM=<platform_subdir> install
```

This will copy the compiled platform specific libraries and firmware files
under the *install/platform/<platform_subdir>/* directory. An alternate
install root directory path can be specified as follows.
```
make PLATFORM=<platform_subdir> I=<install_directory> install
```

In addition, platform specific configuration options can be specified with the
top-level make command line. These options, such as *PLATFORM_<xyz>* or
*FW_<abc>*, are platform specific and described in more details in the
*docs/platform/<platform_name>.md* files and
*docs/firmware/<firmware_name>.md* files.

License
-------

OpenSBI is distributed under the terms of the BSD 2-clause license
("Simplified BSD License" or "FreeBSD License", SPDX: *BSD-2-Clause*).
A copy of this license with OpenSBI copyright can be found in the file
[COPYING.BSD].

All source files in OpenSBI contain the 2-Clause BSD license SPDX short
indentifier in place of the full license text.

```
SPDX-License-Identifier:    BSD-2-Clause
```

This enables machine processing of license information based on the SPDX
License Identifiers that are available on the [SPDX] web site.

OpenSBI source code also contains code reused from other projects as listed
below. The original license text of these projects is included in the source
files where the reused code is present.

1. The libfdt source code is disjunctively dual licensed
   (GPL-2.0+ OR BSD-2-Clause). Some of this project code is used in OpenSBI
   under the terms of the BSD 2-Clause license. Any contributions to this
   code must be made under the terms of both licenses.

Contributing to OpenSBI
-----------------------

The OpenSBI project encourages and welcomes contributions. Contributions should
follow the rules described in OpenSBI [Contribution Guideline] document.
In particular, all patches sent should contain a Signed-off-by tag.

Documentation
-------------

Detailed documentation of various aspects of OpenSBI can be found under the
*docs* directory. The documentation covers the following topics.

* [Contribution Guideline]: Guideline for contributing code to OpenSBI project
* [Library Usage]: API documentation of OpenSBI static library *libsbi.a*
* [Platform Support Guide]: Guideline for implementing support for new platforms
* [Platform Documentation]: Documentation of the platforms currently supported.
* [Firmware Documentation]: Documentation for the different types of firmware
  examples build supported by OpenSBI.

OpenSBI source code is also well documented. For source level documentation,
doxygen style is used. Please refer to [Doxygen manual] for details on this
format.

Doxygen can be installed on Linux distributions using *.deb* packages using
the following command.
```
sudo apt-get install doxygen doxygen-latex doxygen-doc doxygen-gui graphviz
```

For *.rpm* based Linux distributions, the following commands can be used.
```
sudo yum install doxygen doxygen-latex doxywizard graphviz
```
or
```
sudo yum install doxygen doxygen-latex doxywizard graphviz
```

To build a consolidated *refman.pdf* of all documentation, run:
```
make docs
```
or
```
make O=<build_directory> docs
```

the resulting *refman.pdf* will be available under the directory
*<build_directory>/docs/latex*. To install this file, run:
```
make install_docs
```
or
```
make I=<install_directory> install_docs
```

*refman.pdf* will be installed under *<install_directory>/docs*.

[Github]: https://github.com/riscv/riscv-sbi-doc
[U-Boot]: https://www.denx.de/wiki/U-Boot/SourceCode
[COPYING.BSD]: COPYING.BSD
[SPDX]: http://spdx.org/licenses/
[Contribution Guideline]: docs/contributing.md
[Library Usage]: docs/library_usage.md
[Platform Support Guide]: docs/platform_guide.md
[Platform Documentation]: docs/platform/platform.md
[Firmware Documentation]: docs/firmware/fw.md
[Doxygen manual]: http://www.stack.nl/~dimitri/doxygen/manual.html

