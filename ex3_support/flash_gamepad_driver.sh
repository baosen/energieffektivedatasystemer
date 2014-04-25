#!/bin/bash
set -e
ptxdist clean driver-gamepad
ptxdist compile driver-gamepad
ptxdist images root.romfs
ptxdist test flash-rootfs
