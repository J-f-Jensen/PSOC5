# THIS FILE IS AUTOMATICALLY GENERATED
# Project: C:\Users\Bruger\OneDrive\Skrivebord\CODE\PSOC5\CY8CKIT-59-Arduino\CY8CKIT59_Ardudino-Speeduino.cydsn\CY8CKIT59_Ardudino-Speeduino.cyprj
# Date: Tue, 23 Jan 2018 20:39:17 GMT
#set_units -time ns
create_clock -name {ADC_theACLK(routed)} -period 83.333333333333329 -waveform {0 41.6666666666667} [list [get_pins {ClockBlock/dclk_0}]]
create_clock -name {Clock_4(routed)} -period 1000 -waveform {0 500} [list [get_pins {ClockBlock/dclk_1}]]
create_clock -name {Clock_3(routed)} -period 1000000 -waveform {0 500000} [list [get_pins {ClockBlock/dclk_5}]]
create_clock -name {CyILO} -period 10000 -waveform {0 5000} [list [get_pins {ClockBlock/ilo}] [get_pins {ClockBlock/clk_100k}] [get_pins {ClockBlock/clk_1k}] [get_pins {ClockBlock/clk_32k}]]
create_clock -name {CyIMO} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/imo}]]
create_clock -name {CyPLL_OUT} -period 13.888888888888888 -waveform {0 6.94444444444444} [list [get_pins {ClockBlock/pllout}]]
create_clock -name {CyMASTER_CLK} -period 13.888888888888888 -waveform {0 6.94444444444444} [list [get_pins {ClockBlock/clk_sync}]]
create_generated_clock -name {CyBUS_CLK} -source [get_pins {ClockBlock/clk_sync}] -edges {1 3 7} [list [get_pins {ClockBlock/clk_bus_glb}]]
create_clock -name {CyBUS_CLK(fixed-function)} -period 41.666666666666664 -waveform {0 13.8888888888889} [get_pins {ClockBlock/clk_bus_glb_ff}]
create_generated_clock -name {ADC_theACLK} -source [get_pins {ClockBlock/clk_sync}] -edges {1 7 13} [list [get_pins {ClockBlock/dclk_glb_0}]]
create_generated_clock -name {Clock_4} -source [get_pins {ClockBlock/clk_sync}] -edges {1 73 145} [list [get_pins {ClockBlock/dclk_glb_1}]]
create_clock -name {Clock_4(fixed-function)} -period 1000 -waveform {0 13.8888888888889} [get_pins {ClockBlock/dclk_glb_ff_1}]
create_generated_clock -name {Clock_9} -source [get_pins {ClockBlock/clk_sync}] -edges {1 73 145} [list [get_pins {ClockBlock/dclk_glb_2}]]
create_clock -name {Clock_9(fixed-function)} -period 1000 -waveform {0 13.8888888888889} [get_pins {ClockBlock/dclk_glb_ff_2}]
create_generated_clock -name {CLK_PC1} -source [get_pins {ClockBlock/clk_sync}] -edges {1 73 145} [list [get_pins {ClockBlock/dclk_glb_3}]]
create_generated_clock -name {Clock_2} -source [get_pins {ClockBlock/clk_sync}] -edges {1 721 1441} [list [get_pins {ClockBlock/dclk_glb_4}]]
create_clock -name {Clock_2(fixed-function)} -period 10000 -waveform {0 13.8888888888889} [get_pins {ClockBlock/dclk_glb_ff_4}]
create_generated_clock -name {Clock_3} -source [get_pins {ClockBlock/clk_sync}] -edges {1 72001 144001} [list [get_pins {ClockBlock/dclk_glb_5}]]

set_false_path -from [get_pins {__ONE__/q}]
set_false_path -from [get_pins {__ZERO__/q}]

# Component constraints for C:\Users\Bruger\OneDrive\Skrivebord\CODE\PSOC5\CY8CKIT-59-Arduino\CY8CKIT59_Ardudino-Speeduino.cydsn\TopDesign\TopDesign.cysch
# Project: C:\Users\Bruger\OneDrive\Skrivebord\CODE\PSOC5\CY8CKIT-59-Arduino\CY8CKIT59_Ardudino-Speeduino.cydsn\CY8CKIT59_Ardudino-Speeduino.cyprj
# Date: Tue, 23 Jan 2018 20:39:01 GMT
