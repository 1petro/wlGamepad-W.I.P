project('wlgamepad', 'c', version: '0.2-beta', default_options: ['c_std=c99'])

cc = meson.get_compiler('c')

wayland_protos = dependency('wayland-protocols', version: '>=1.14')
wl_protocol_dir = wayland_protos.get_pkgconfig_variable('pkgdatadir')
wayland_scanner = find_program('wayland-scanner')
wayland_client = dependency('wayland-client')
rt = cc.find_library('rt')

optvalue = get_option('allow_debug')
if optvalue
add_project_arguments('-DDEBUG', language: 'c')
endif

xdg_shell_h = custom_target(
	'xdg-shell-client-protocol.h',
	output: 'xdg-shell-client-protocol.h',
	command: [wayland_scanner, 'client-header', wl_protocol_dir + '/stable/xdg-shell/xdg-shell.xml', '@OUTPUT@'],
)

xdg_shell_c = custom_target(
	'xdg-shell-client-protocol.c',
	output: 'xdg-shell-client-protocol.c',
	command: [wayland_scanner, 'private-code', wl_protocol_dir + '/stable/xdg-shell/xdg-shell.xml', '@OUTPUT@'],
)

wlr_layer_shell_unstable_v1_h = custom_target(
	'wlr-layer-shell-unstable-v1.h',
	output: 'wlr-layer-shell-unstable-v1.h',
	command: [wayland_scanner, 'client-header', meson.source_root() + '/wlr-protocols/unstable/wlr-layer-shell-unstable-v1.xml', '@OUTPUT@'],
)

wlr_layer_shell_unstable_v1_c = custom_target(
	'wlr-layer-shell-unstable-v1.c',
	output: 'wlr-layer-shell-unstable-v1.c',
	command: [wayland_scanner, 'private-code', meson.source_root() + '/wlr-protocols/unstable/wlr-layer-shell-unstable-v1.xml', '@OUTPUT@'],
)

xdg_shell_lib = static_library('xdg_shell_lib', [xdg_shell_c, xdg_shell_h])
xdg_shell = declare_dependency(link_with: xdg_shell_lib)

wlr_layer_shell_unstable_v1_lib = static_library('wlr_layer_shell_unstable_v1_lib', [wlr_layer_shell_unstable_v1_c, wlr_layer_shell_unstable_v1_h])
wlr_layer_shell_unstable_v1 = declare_dependency(link_with: wlr_layer_shell_unstable_v1_lib)

inc = include_directories('src/libevdev')

libpng = dependency('libpng16')

executable(
	'wlgp',
	['src/main.c','src/wlgp-gui.c','src/draw.c','src/wlgp-input.c','src/libevdev/libevdev.c','src/image.c','src/config.c','src/libevdev/libevdev-names.c','src/layout.c'], 
        link_args : ['-lm','-lpng'],
	include_directories : inc,
	dependencies: [wayland_client, wlr_layer_shell_unstable_v1, xdg_shell, rt], 
	install: true
)

executable(
        'wlgp-edit',
        ['gui-editor/main.c','gui-editor/layout-edit.c','src/wlgp-gui.c','src/draw.c','src/wlgp-input.c','src/libevdev/libevdev.c','src/image.c','src/config.c','src/libevdev/libevdev-names.c','src/layout.c'],
        link_args : ['-lm','-lpng'],
        include_directories : inc,
        dependencies: [wayland_client, wlr_layer_shell_unstable_v1, xdg_shell, rt],
        install: true
)
