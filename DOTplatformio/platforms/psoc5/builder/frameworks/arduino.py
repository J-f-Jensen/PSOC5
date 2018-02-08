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

"""
Arduino

Arduino Wiring-based Framework allows writing cross-platform software to
control devices attached to a wide range of Arduino boards to create all
kinds of creative coding, interactive objects, spaces or physical experiences.

http://arduino.cc/en/Reference/HomePage
"""

from os import listdir
from os.path import isdir, isfile, join

from SCons.Script import DefaultEnvironment

env = DefaultEnvironment()
platform = env.PioPlatform()

FRAMEWORK_DIR = platform.get_package_dir("framework-arduinopsoc5")
FRAMEWORK_VERSION = platform.get_package_version("framework-arduinopsoc5")
assert isdir(FRAMEWORK_DIR)


#BUILTIN_USB_FLAGS = (
#    "USB_AUDIO",
#    "USB_HID",
#    "USB_SERIAL_HID",
#    "USB_DISK",
#    "USB_DISK_SDFLASH",
#    "USB_MIDI",
#    "USB_RAWHID",
#    "USB_FLIGHTSIM",
#    "USB_DISABLED"
#)


#if not any(f in env.get("BUILD_FLAGS", []) for f in BUILTIN_USB_FLAGS):
#    env.Append(CPPDEFINES=["USB_SERIAL"])

env.Append(
    CPPDEFINES=[
        ("ARDUINO", 10610)#,
#        "BOARD_%s" % board.get("build.variant")
    ],

    CPPPATH=[
		join(FRAMEWORK_DIR, "cores", env.BoardConfig().get("build.core")),
		join(FRAMEWORK_DIR, "cores", env.BoardConfig().get("build.core"), "libpsoc5")
		
    ],
	
	LIBPATH=[
		join(FRAMEWORK_DIR, "cores", env.BoardConfig().get("build.core")),
		join(FRAMEWORK_DIR, "cores", env.BoardConfig().get("build.core"), "libpsoc5")
        
	],

    LIBSOURCE_DIRS=[
        join(FRAMEWORK_DIR, "libraries"),
		join(FRAMEWORK_DIR, "variants", env.BoardConfig().get("build.variant"))
    ]
)

env.Prepend(LIBPATH=[join(FRAMEWORK_DIR, "cores", env.BoardConfig().get("build.core"))])


#
# Target: Build Core Library
#

libs = []

if "build.variant" in env.BoardConfig():
	libs.append(File([join(FRAMEWORK_DIR, "variants", env.BoardConfig().get("build.variant"),"CyCompLib.a")]))
	if "CY8CKIT-059-Speeduino" in (env.BoardConfig().get("build.core")):
		libs.append(File([join(FRAMEWORK_DIR, "variants", env.BoardConfig().get("build.variant"),"CY8CKIT59_Ardudino-Speeduino.a")]))
	elif "CY8CKIT59_Ardudino-SpeeduinoWBO2" in (env.BoardConfig().get("build.core")):
		libs.append(File([join(FRAMEWORK_DIR, "variants", env.BoardConfig().get("build.variant"),"CY8CKIT59_Ardudino-Speeduino-WBO2.a")]))
	elif "CY8CKIT-059" in (env.BoardConfig().get("build.core")):
		libs.append(File([join(FRAMEWORK_DIR, "variants", env.BoardConfig().get("build.variant"),"CY8CKIT59_Ardudino.a")]))
	else:
		libs.append(File([join(FRAMEWORK_DIR, "variants", env.BoardConfig().get("build.variant"),"Uno_blocks.a")]))


if "build.variant" in env.BoardConfig():
    env.Append(
        CPPPATH=[
            join(FRAMEWORK_DIR, "variants",
                 env.BoardConfig().get("build.variant"))
        ]
    )
    libs.append(env.BuildLibrary(
        join("$BUILD_DIR", "FrameworkArduinoVariant"),
        join(FRAMEWORK_DIR, "variants", env.BoardConfig().get("build.variant"))
    ))
	


libs.append(env.BuildLibrary(
    join("$BUILD_DIR", "FrameworkArduino"),
    join(FRAMEWORK_DIR, "cores", env.BoardConfig().get("build.core"))
))

env.Prepend(LIBS=libs)

# You can enable the follwing lines to debug the build, in a PIO terminal run the build by executing: pio run -v
#env.Execute("rem Nothing")
#env.Execute("rem CPPPATH $CPPPATH")
#env.Execute("rem CPPDEFINES $CPPDEFINES" )
#env.Execute("rem LIBSUFFIXES $LIBSUFFIXES" )
#env.Execute("rem LIBLINKPREFIX $LIBLINKPREFIX" )
#env.Execute("rem LIBPATH $LIBPATH" )
#env.Execute("rem _LIBFLAGS $_LIBFLAGS" )
#env.Execute("rem _LIBDIRFLAGS $_LIBDIRFLAGS" )
#env.Execute("rem LIBS $LIBS" )
#env.Execute("rem Nothing")
#print env.Dump()