# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/ian/esp/esp-idf/components/bootloader/subproject"
  "/home/ian/Documentos/Alcantara_ESP/build/bootloader"
  "/home/ian/Documentos/Alcantara_ESP/build/bootloader-prefix"
  "/home/ian/Documentos/Alcantara_ESP/build/bootloader-prefix/tmp"
  "/home/ian/Documentos/Alcantara_ESP/build/bootloader-prefix/src/bootloader-stamp"
  "/home/ian/Documentos/Alcantara_ESP/build/bootloader-prefix/src"
  "/home/ian/Documentos/Alcantara_ESP/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/ian/Documentos/Alcantara_ESP/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/ian/Documentos/Alcantara_ESP/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
