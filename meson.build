project('Kinetica', 'cpp',
  version : '0.6',
  default_options : ['warning_level=1', 'cpp_std=c++14'])

cc = meson.get_compiler('cpp')

# Dependencies
sdl_dep = dependency('sdl2')
if host_machine.system() == 'darwin'
  gl_dep = dependency('appleframeworks', modules : ['OpenGL', 'GLUT'])
  glu_dep = [] # GLU is part of OpenGL framework
else
  gl_dep = dependency('gl')
  glu_dep = dependency('glu')
endif

openal_dep = dependency('openal')
glew_dep = dependency('glew')
sdl_image_dep = dependency('SDL2_image')
sdl_mixer_dep = dependency('SDL2_mixer', required : false)

# Include Directories
inc = include_directories('source/include', 'source/generic', 'source', 'source/projectspecific', 'source/sky')

# Sources
sources = [
  'source/main.cpp',
  'source/projectspecific/ms3d/mathlib.cpp',
  'source/projectspecific/ms3d/msModel.cpp',
  
  # OVR Kernel Common
  'source/include/Kernel/OVR_Alg.cpp',
  'source/include/Kernel/OVR_Allocator.cpp',
  'source/include/Kernel/OVR_Atomic.cpp',
  'source/include/Kernel/OVR_File.cpp',
  'source/include/Kernel/OVR_FileFILE.cpp',
  'source/include/Kernel/OVR_Log.cpp',
  'source/include/Kernel/OVR_Math.cpp',
  'source/include/Kernel/OVR_RefCount.cpp',
  'source/include/Kernel/OVR_Std.cpp',
  'source/include/Kernel/OVR_String.cpp',
  'source/include/Kernel/OVR_String_FormatUtil.cpp',
  'source/include/Kernel/OVR_String_PathUtil.cpp',
  'source/include/Kernel/OVR_SysFile.cpp',
  'source/include/Kernel/OVR_System.cpp',
  'source/include/Kernel/OVR_Timer.cpp',
  'source/include/Kernel/OVR_UTF8Util.cpp',
  
  # OVR Device Common
  'source/include/OVR_DeviceHandle.cpp',
  'source/include/OVR_DeviceImpl.cpp',
  'source/include/OVR_LatencyTestImpl.cpp',
  'source/include/OVR_SensorFilter.cpp',
  'source/include/OVR_SensorFusion.cpp',
  'source/include/OVR_SensorImpl.cpp',
  'source/include/OVR_ThreadCommandQueue.cpp',
  
  # OVR Util
  'source/include/Util/Util_LatencyTest.cpp',
  'source/include/Util/Util_MagCalibration.cpp',
  'source/include/Util/Util_Render_Stereo.cpp',
]

# Platform Specific
if host_machine.system() == 'darwin'
  sources += [
    'source/include/Kernel/OVR_ThreadsPthread.cpp',
    'source/include/OVR_OSX_DeviceManager.cpp',
    'source/include/OVR_OSX_HIDDevice.cpp',
    'source/include/OVR_OSX_HMDDevice.cpp',
    'source/include/OVR_OSX_SensorDevice.cpp',
  ]
  add_project_arguments('-D__MACOSX__', language : 'cpp')
  add_project_arguments('-DGL_SILENCE_DEPRECATION', language : 'cpp')
  
elif host_machine.system() == 'windows'
  sources += [
    'source/include/Kernel/OVR_ThreadsWinAPI.cpp',
    'source/include/OVR_Win32_DeviceManager.cpp',
    'source/include/OVR_Win32_DeviceStatus.cpp',
    'source/include/OVR_Win32_HIDDevice.cpp',
    'source/include/OVR_Win32_HMDDevice.cpp',
    'source/include/OVR_Win32_SensorDevice.cpp',
  ]
  add_project_arguments('-D_WIN32', language : 'cpp')
elif host_machine.system() == 'linux'
  sources += [
    'source/include/Kernel/OVR_ThreadsPthread.cpp',
  ]
  add_project_arguments('-D__LINUX__', language : 'cpp')
endif

deps = [sdl_dep, gl_dep, glu_dep, openal_dep, glew_dep, sdl_image_dep]
if sdl_mixer_dep.found()
  deps += sdl_mixer_dep
endif

if host_machine.system() == 'darwin'
  deps += dependency('appleframeworks', modules : ['IOKit', 'CoreFoundation', 'CoreGraphics'])
endif

executable('kinetica', sources,
  dependencies : deps,
  include_directories : inc,
  install : true
)
