# Copyright 2014-present PlatformIO <contact@platformio.org>
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#    http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

from os.path import join
from time import sleep
#from SCons.Script import AlwaysBuild, Builder, Default, DefaultEnvironment

from SCons.Script import (ARGUMENTS, COMMAND_LINE_TARGETS, AlwaysBuild,
                          Builder, Default, DefaultEnvironment)

from platformio.util import get_serialports

env = DefaultEnvironment()

env.Replace(
    AR="arm-none-eabi-ar",
    AS="arm-none-eabi-as",
    CC="arm-none-eabi-gcc",
    CXX="arm-none-eabi-g++",
    GDB="arm-none-eabi-gdb",
    OBJCOPY="arm-none-eabi-objcopy",
    RANLIB="arm-none-eabi-ranlib",
    SIZETOOL="arm-none-eabi-size",

    ARFLAGS=["rcs"],

    ASFLAGS=["-x", "assembler-with-cpp"],

    CFLAGS=[
        "-std=gnu11"
	],

    CCFLAGS=[
		"-D NDEBUG",
		"-Wall",
		"-ffunction-sections",
		"-O3",
		"-mcpu=%s" % env.BoardConfig().get("build.cpu"),
		"-mthumb",
		"-ffat-lto-objects",
		"-g",
		#"-specs=nano.specs",
		#"-specs=nosys.specs",
		"-Wno-main"
    ],
	
    CXXFLAGS=[
	    "-fno-rtti",
        "-fno-exceptions", #Performance - but is it needed?
		"-std=gnu++11",
		"-fpermissive" # Needed in speedoino - but I would rather correct the code! Have to do this later
    ],

    CPPDEFINES=[
        ("F_CPU", "$BOARD_F_CPU")#,
        #"USBCON"
    ],

    LINKFLAGS=[
        "-O3",
        "-mthumb",
        "-mcpu=%s" % env.BoardConfig().get("build.cpu"),
		"-g",
		"-ffunction-sections",
		"-ffat-lto-objects",
		"-Wl,-Map,%s\\test.map" % ("$BUILD_DIR"),
		"-specs=nano.specs",
		"-specs=nosys.specs",
		"-Wl,--gc-sections"
    ],

    #LIBS=["c", "gcc", "m", "nosys"],
	LIBS=["stdc++"],
	

    SIZEPRINTCMD='$SIZETOOL -B -d $SOURCES',

    PROGNAME="firmware",
    PROGSUFFIX=".elf"
)

env.Append(
    ASFLAGS=env.get("CCFLAGS", [])[:],

    BUILDERS=dict(
        ElfToBin=Builder(
            action=env.VerboseAction(" ".join([
                "$OBJCOPY",
                "-O",
                "binary",
                "$SOURCES",
                "$TARGET"
            ]), "Building $TARGET"),
            suffix=".bin"
        ),
        ElfToHex=Builder(
            action=env.VerboseAction(" ".join([
				"$OBJCOPY",
				"-O ihex -R .cyeeprom -R .cyconfigecc -R .cycustnvl -R .cywolatch -R .cyflashprotect -R .cybootloader -R .cyloadablemeta -R .cyloadermeta -R .cymeta ",
                "$SOURCES",
                "$TARGET"
            ]), "Building $TARGET"),
            suffix=".hex"
        )
    )
)


# The source code of "platformio-build-tool" is here
# https://github.com/platformio/platformio-core/blob/develop/platformio/builder/tools/platformio.py

#
# Target: Build executable and linkable firmware
#
target_elf = env.BuildProgram()

#
# Target: Build the .bin file
#
target_bin = env.ElfToHex(join("$BUILD_DIR", "firmware"), target_elf)

#
# Target: Print binary size
#

target_size = env.Alias(
    "size", target_elf,
    env.VerboseAction("$SIZEPRINTCMD", "Calculating size $SOURCE"))
AlwaysBuild(target_size)

# 2017.11.18

def BeforeUpload(target, source, env):  # pylint: disable=W0613,W0621

    if "program" in COMMAND_LINE_TARGETS:
        return

    upload_options = {}
    if "BOARD" in env:
        upload_options = env.BoardConfig().get("upload", {})

    if env.subst("$UPLOAD_SPEED"):
        env.Append(UPLOADERFLAGS=["-b", "$UPLOAD_SPEED"])
		
    # extra upload flags
    if "extra_flags" in upload_options:
        env.Append(UPLOADERFLAGS=upload_options.get("extra_flags"))

    if upload_options and not upload_options.get("require_upload_port", False):
        return
		
    env.AutodetectUploadPort()
	
    env.Append(UPLOADERFLAGS=["-P", '"$UPLOAD_PORT"'])

    if not upload_options.get("disable_flushing", False) \
        and not env.get("UPLOAD_PORT", "").startswith("net:"):
        env.FlushSerialBuffer("$UPLOAD_PORT")

    before_ports = get_serialports()

    if upload_options.get("use_1200bps_touch", False):
        env.TouchSerialPort("$UPLOAD_PORT", 1200)
		
    if upload_options.get("wait_for_upload_port", False):
        env.Replace(UPLOAD_PORT=env.WaitForNewSerialPort(before_ports))
		
env.Replace(
	UPLOADER="avrdude",
	UPLOADERFLAGS=[
		"-p", "psoc059",
		"-C",
		join(env.PioPlatform().get_package_dir("framework-arduinopsoc5") or "",
			 "avrdude.conf"),
		"-c", "$UPLOAD_PROTOCOL"
	],
	UPLOADHEXCMD='$UPLOADER $UPLOADERFLAGS -D -U flash:w:$SOURCES:i',
)

#
# Target: Upload firmware
#
target_upload = env.Alias(
    "upload", target_bin,
    [env.VerboseAction(BeforeUpload, "Looking for upload port..."),
     env.VerboseAction("$UPLOADHEXCMD", "Uploading $SOURCE")])
AlwaysBuild(target_upload)

#
# Target: Define targets
#
Default(target_bin,target_size)