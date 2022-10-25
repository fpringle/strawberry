# Copyright (c) 2022, Frederick Pringle
# All rights reserved.
# 
# This source code is licensed under the BSD-style license found in the
# LICENSE file in the root directory of this source tree.

TEMPLATE = subdirs

SUBDIRS = core \
          gui \
          uci

core.subdir = src/core
gui.subdir = src/gui
uci.subdir = src/uci

gui.depends = core
uci.depends = core
