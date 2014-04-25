#!/bin/bash
set -e
ptxdist clean game
ptxdist compile game
ptxdist images root.romfs
ptxdist test flash-rootfs
