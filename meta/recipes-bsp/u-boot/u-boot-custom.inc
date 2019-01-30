# Custom U-Boot build
#
# This software is a part of ISAR.
# Copyright (c) Siemens AG, 2018
#
# SPDX-License-Identifier: MIT

FILESPATH =. "${LAYERDIR_core}/recipes-bsp/u-boot/files:"

DESCRIPTION ?= "Custom U-Boot"

PROVIDES += "u-boot-${MACHINE} u-boot-${MACHINE}-dev u-boot-tools"

inherit dpkg

SRC_URI += "file://debian/"

U_BOOT_BUILD_DEPENDS ?= "bc, bison, flex, device-tree-compiler"

export U_BOOT_CONFIG
export U_BOOT_BIN

do_prepare_build() {
    cp -r ${WORKDIR}/debian ${S}/
    export BUILD_DEPENDS="${U_BOOT_BUILD_DEPENDS}"
    transform_template "${S}/debian/changelog.tmpl" "${S}/debian/changelog"
    transform_template "${S}/debian/control.tmpl" "${S}/debian/control"

    echo "${U_BOOT_BIN} /usr/lib/u-boot/${MACHINE}" > \
        ${S}/debian/u-boot-${MACHINE}.install

    echo "tools/env/libubootenv.a usr/lib" > \
        ${S}/debian/u-boot-${MACHINE}-dev.install
}
