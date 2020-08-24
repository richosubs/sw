connect -url tcp:127.0.0.1:3121
source C:/Xilinx/Vitis/2019.2/scripts/vitis/util/zynqmp_utils.tcl
targets -set -nocase -filter {name =~"APU*"}
rst -system
after 3000
targets -set -filter {jtag_cable_name =~ "Avnet USB-to-JTAG/UART Pod V1 1234-oj1A" && level==0} -index 0
fpga -file C:/Users/richo/ws/sys/sw/workspace/app_prj_base2/_ide/bitstream/prj_base.bit
targets -set -nocase -filter {name =~"APU*"}
loadhw -hw C:/Users/richo/ws/sys/sw/workspace/platform_prj_base/export/platform_prj_base/hw/prj_base.xsa -mem-ranges [list {0x80000000 0xbfffffff} {0x400000000 0x5ffffffff} {0x1000000000 0x7fffffffff}]
configparams force-mem-access 1
targets -set -nocase -filter {name =~"APU*"}
set mode [expr [mrd -value 0xFF5E0200] & 0xf]
targets -set -nocase -filter {name =~ "*A53*#0"}
rst -processor
dow C:/Users/richo/ws/sys/sw/workspace/platform_prj_base/export/platform_prj_base/sw/platform_prj_base/boot/fsbl.elf
set bp_21_15_fsbl_bp [bpadd -addr &XFsbl_Exit]
con -block -timeout 60
bpremove $bp_21_15_fsbl_bp
targets -set -nocase -filter {name =~ "*A53*#0"}
rst -processor
dow C:/Users/richo/ws/sys/sw/workspace/app_prj_base2/Debug/app_prj_base2.elf
configparams force-mem-access 0
targets -set -nocase -filter {name =~ "*A53*#0"}
con
