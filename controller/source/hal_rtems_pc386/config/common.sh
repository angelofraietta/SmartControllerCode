#
#  Some shell functions and shared setup shared across the build scripts
#
#  Including this file assumes these are defined:
#
#  CPU        - user argument
#  my_exit()  - shell script specific exit routine
#  usage()    - shell script usage routine
#
#  Including this file sets:
#
#  target   - to the GNU tools target name
#  CPU      - to the canonical RTEMS CPU
#
#
#  $Id: common.sh,v 1.1 2003/03/05 04:36:25 angelo Exp $
#

#
#  Checks the status returned by executables and exits if it is non-zero.
#
check_fatal()
{
  if [ $1 -ne 0 ] ; then
    shift
    echo "ERROR: $*" >&2
    my_exit 1
  fi
  #echo
  #echo "End of $*"
  #echo -n "Press return to continue> "
  #echo
  #read line
}

print_rtems_cpus()
{
  echo
  echo "CPU is one of the following: "
  echo "  hppa1.1		i386		i386-coff	i386-elf"
  echo "  i386-go32		i960		i960-coff	i960-elf"
  echo "  m68k			m68k-coff	m68k-elf	mips64orion"
  echo "  powerpc		sh		sh-coff		sh-elf"
  echo "  sparc			sparc-aout	sparc-elf"
  echo 
  echo "Formats without a -XXX suffix are the preferred target."
  echo 
  echo "CPU-rtems is used as the GNU target and results in:"
  echo "    hppa1.1-rtems     -- Hewlett Packard PA-RISC"
  echo "    i386-rtems        -- Intel i386 and above in protected mode (ELF)"
  echo "    i386-rtemself     -- Intel i386 and above in protected mode (ELF)"
  echo "    i386-rtemscoff    -- Intel i386 and above in protected mode (COFF)"
  echo "    i386-go32-rtems   -- PC clone using DJGPP V1.x and GO32"
  echo "    i960-rtems        -- Intel i960 (COFF)"
  echo "    i960-rtemscoff    -- Intel i960 (COFF)"
  echo "    i960-rtemself     -- Intel i960 (ELF)"
  echo "    m68k-rtems        -- Motorola mc680x0, mc683xx, and ColdFire (COFF)"
  echo "    m68k-rtemself     -- Motorola mc680x0, mc683xx, and ColdFire (ELF)"
  echo "    m68k-rtemscoff    -- Motorola mc680x0, mc683xx, and ColdFire (ELF)"
  echo "    mips64orion-rtems -- MIPS64"
  echo "    powerpc-rtems     -- IBM and Motorola PowerPC"
  echo "    sh-rtems          -- Hitachi SH (COFF)"
  echo "    sh-rtemscoff      -- Hitachi SH (COFF)"
  echo "    sh-rtemself       -- Hitachi SH (ELF)"
  echo "    sparc-rtems       -- SPARC (ELF)"
  echo "    sparc-rtemself    -- SPARC (ELF)"
  echo "    sparc-rtemsaout   -- SPARC (A.OUT)"
}

make_one_tree()
{
  my_pwd=`pwd`
  echo
  echo "Building src subdirectory ..."
  echo "  This directory contains symbolic links to gcc, newlib, and"
  echo "  binutils so they can be configured and built together."
  echo

  rm -rf src
  mkdir src
  cd src

  # The configure scripts and share libraries should be taken from
  # the tool component with the newest version.
  GET_CONFIGURE_SCRIPTS_FROM=${BINUTILS} 
  for f in config config-ml.in config.guess config.if config.sub \
        configure configure.in etc Makefile.in install-sh libiberty \
        ltconfig ltmain.sh missing mkinstalldirs move-if-change \
        symlink-tree ylwrap
  do
        ln -s ../${GET_CONFIGURE_SCRIPTS_FROM}/$f .
  done

  # Link in GCC or EGCS
  case ${GCC} in
     gcc-2.[78]*)
        ln -s ../${GCC} gcc
        ;;
     egcs-1*|gcc-2.9*)
        for f in gcc include libio libstdc++ texinfo xiberty
        do
            ln -s ../${GCC}/${f} .
        done
        ;;
     *)
        echo "Unknown version of GCC (${GCC})."
        echo "common.sh does not know how to build a one-tree style src tree."
        exit 1
        ;;
  esac

  # Get these components from binutils
  for f in bfd binutils gas gprof ld opcodes
  do
       ln -s ../${BINUTILS}/$f .
  done

  # Now get the C library
  ln -s ../${NEWLIB}/newlib .

  # return to the main tools directory
  cd ${my_pwd}
}

preinstall_header_files()
{
  for dir in ${INSTALL_POINT}/${target} \
             ${INSTALL_POINT}/${target}/include \
             ${INSTALL_POINT}/${target}/sys-include
  do
    if [ ! -d ${dir} ] ; then
      echo "Making directory ${dir} ..."
      mkdir -p ${dir}
      check_fatal $?  "**** FAILED **** unable to make directory (${dir})"
    fi
  done

  srclimits=../${NEWLIB}/newlib/libc/sys/rtems/include/limits.h
  test -r ${srclimits}
  check_fatal $?  "**** FAILED **** unable to find ${srclimits}"

  for dir in ${INSTALL_POINT}/${target}/include \
             ${INSTALL_POINT}/${target}/sys-include
  do
    cp ${srclimits} ${dir}
    check_fatal $?  "**** FAILED **** unable to install ${dir}/limits.h"
  done
}

#
#  Figure out if GNU makeinfo is available
#

makeinfo_test()
{
  if [ "x${BUILD_DOCS}" = "xyes" ] ; then
    makeinfo_found=no
    for name in makeinfo
    do
      if [ ${makeinfo_found} = "no" ] ; then
        ${name} --version >/dev/null 2>&1
        if [ $? -eq 0 ] ; then
          MAKEINFO=${name}
          makeinfo_found=yes
        fi
      fi
    done

    if [ ${makeinfo_found} = "no" ] ; then
      echo "Unable to locate a version of GNU makeinfo in your PATH"
      echo "GNU makeinfo is required to build the documentation."
      exit 1
    else
      echo "GNU makeinfo 1.68 or newer is required to build some of the"
      echo "documentation included with this package.  You have version"
      echo
      makeinfo --version
    fi
  fi
}

# CPU must be set before we run any of this stuff
test "x${CPU}" != "x" || check_fatal $? "(common.sh) CPU not set"

# The argument to the "--target" argument of configure.
target=${CPU}-rtems
BUILDDIR=build-${CPU}-${BUILD_PIECE}

case ${CPU} in
  hppa1.1)     ;;
  i386)        ;;
  i386-coff)   CPU=i386; target=i386-rtemscoff ;;
  i386-elf)    CPU=i386; target=i386-rtemself ;;
  i386-go32)   ;;
  i960)        ;;
  i960-coff)   CPU=i960; target=i960-rtemscoff ;;
  i960-elf)    CPU=i960; target=i960-rtemself ;;
  m68k)        ;;
  m68k-coff)   CPU=m68k; target=m68k-rtemscoff ;;
  m68k-elf)    CPU=m68k; target=m68k-rtemself ;;
  mips64orion) ;;
  powerpc)     ;;
  sh)          ;;
  sh-coff)     CPU=sh; target=sh-rtemscoff;;
  sh-elf)      CPU=sh; target=sh-rtemself;;
  sparc)       ;;
  sparc-aout)  CPU=sparc; target=sparc-rtemsaout;;
  sparc-elf)   CPU=sparc; target=sparc-rtemself;;
  *)  
     echo ${CPU} is not a supported CPU
     echo
     usage
     exit 1
     ;;
esac
 
#
#  Figure out if GNU make is available
#
gmake_found=no
for name in gmake make
do
  if [ ${gmake_found} = "no" ] ; then
    ${name} --version >/dev/null 2>&1
    if [ $? -eq 0 ] ; then
      MAKE=${name}
      gmake_found=yes 
    fi
  fi

done

if [ ${gmake_found} = "no" ] ; then
   echo "Unable to locate a version of GNU make in your PATH"
   echo "GNU Make is required to build these tools."
   exit 1
fi
