#ifndef MCP23017_H
#define MCP23017_H

/*
 *      This program is free software; you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation; either version 2 of the License, or
 *      (at your option) any later version.
 *
 *      This program is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *
 *      You should have received a copy of the GNU General Public License
 *      along with this program; if not, write to the Free Software
 *      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *      MA 02110-1301, USA.
 */

/* ------------------------------ MCP23017 WIRING ------------------------------------

Basic Address:  00100 A2 A1 A0 (from 0x20 to 0x27)
A2,A1,A0 tied to ground = 0x20
                __ __
        IOB-0 [|  U  |] IOA-7
        IOB-1 [|     |] IOA-6
        IOB-2 [|     |] IOA-5
        IOB-3 [|     |] IOA-4
        IOB-4 [|     |] IOA-3
        IOB-5 [|     |] IOA-2
        IOB-6 [|     |] IOA-1
        IOB-7 [|     |] IOA-0
        ++++  [|     |] INT-A
        GND   [|     |] INT-B
        -NC-  [|     |] RST (connect to +)
        SCL   [|     |] A2
        SDA   [|     |] A1
        -NC-  [|_____|] A0
*/

/**************************************************************************
    I2C DEVICE ADDRESS
**************************************************************************/
                                            // 0100 A2 A1 A0
#define MCP23017_ADDRESS_DEFAULT_20     0x20    // 0100 0  0  0
#define MCP23017_ADDRESS_DEFAULT_21     0x21    // 0100 0  0  1
#define MCP23017_ADDRESS_DEFAULT_22     0x22    // 0100 0  1  0
#define MCP23017_ADDRESS_DEFAULT_23     0x23    // 0100 0  1  1
#define MCP23017_ADDRESS_DEFAULT_24     0x24    // 0100 1  0  0
#define MCP23017_ADDRESS_DEFAULT_25     0x25    // 0100 1  0  1
#define MCP23017_ADDRESS_DEFAULT_26     0x26    // 0100 1  1  0
#define MCP23017_ADDRESS_DEFAULT_27     0x27    // 0100 1  1  1

/**************************************************************************
    REGISTERS ADDRESS
**************************************************************************/
//BANK = 1
#define MCP23017_ADDRESS_IODIRA     0x00	//< Controls the direction of the data I/O for port A.
#define MCP23017_ADDRESS_IODIRB		0x01    //< Controls the direction of the data I/O for port B.
#define MCP23017_ADDRESS_IPOLA		0x02	//< Configures the polarity on the corresponding GPIO port bits for port A.
#define MCP23017_ADDRESS_IPOLB		0x03	//< Configures the polarity on the corresponding GPIO port bits for port B.
#define MCP23017_ADDRESS_GPINTENA	0x04	//< Controls the interrupt-on-change for each pin of port A.
#define MCP23017_ADDRESS_GPINTENB	0x05	//< Controls the interrupt-on-change for each pin of port B.
#define MCP23017_ADDRESS_DEFVALA	0x06	//< Controls the default comparaison value for interrupt-on-change for port A.
#define MCP23017_ADDRESS_DEFVALB	0x07	//< Controls the default comparaison value for interrupt-on-change for port B.
#define MCP23017_ADDRESS_INTCONA	0x08	//< Controls how the associated pin value is compared for the interrupt-on-change for port A.
#define MCP23017_ADDRESS_INTCONB	0x09	//< Controls how the associated pin value is compared for the interrupt-on-change for port B.
#define MCP23017_ADDRESS_IOCONA		0x0A	//< Controls the device.
#define MCP23017_ADDRESS_IOCONB		0x0B	//< Controls the device.
#define MCP23017_ADDRESS_GPPUA		0x0C	//< Controls the pull-up resistors for the port A pins.
#define MCP23017_ADDRESS_GPPUB		0x0D	//< Controls the pull-up resistors for the port B pins.
#define MCP23017_ADDRESS_INTFA		0x0E	//< Reflects the interrupt condition on the port A pins.
#define MCP23017_ADDRESS_INTFB		0x0F	//< Reflects the interrupt condition on the port B pins.
#define MCP23017_ADDRESS_INTCAPA	0x10	//< Captures the port A value at the time the interrupt occured.
#define MCP23017_ADDRESS_INTCAPB	0x11	//< Captures the port B value at the time the interrupt occured.
#define MCP23017_ADDRESS_GPIOA		0x12	//< Reflects the value on the port A.
#define MCP23017_ADDRESS_GPIOB		0x13	//< Reflects the value on the port B.
#define MCP23017_ADDRESS_OLATA		0x14	//< Provides access to the port A output latches.
#define MCP23017_ADDRESS_OLATB		0x15	//< Provides access to the port B output latches.

//BANK = 0
#define MCP23017_ADDRESS_IODIR      0x00	//< Controls the direction of the data I/O for port A.
#define MCP23017_ADDRESS_IPOL		0x02	//< Configures the polarity on the corresponding GPIO port bits for port A.
#define MCP23017_ADDRESS_GPINTEN	0x04	//< Controls the interrupt-on-change for each pin of port A.
#define MCP23017_ADDRESS_DEFVAL 	0x06	//< Controls the default comparaison value for interrupt-on-change for port A.
#define MCP23017_ADDRESS_INTCON 	0x08	//< Controls how the associated pin value is compared for the interrupt-on-change for port A.
#define MCP23017_ADDRESS_IOCON		0x0A	//< Controls the device.
#define MCP23017_ADDRESS_GPPU		0x0C	//< Controls the pull-up resistors for the port A pins.
#define MCP23017_ADDRESS_INTF		0x0E	//< Reflects the interrupt condition on the port A pins.
#define MCP23017_ADDRESS_INTCAP 	0x10	//< Captures the port A value at the time the interrupt occured.
#define MCP23017_ADDRESS_GPIO		0x12	//< Reflects the value on the port A.
#define MCP23017_ADDRESS_OLAT		0x14	//< Provides access to the port A output latches.

/**************************************************************************
    IODIR: I/O DIRECTION REGISTER (ADDR 0x00)
**************************************************************************/
/*
 * bit 7-0          IO<7:0>: Controls the direction of data I/O <7:0>
                    1 = Pin is configured as an input.
                    0 = Pin is configured as an output.
*/

#define IODIR_REGISTER 0x00

/**************************************************************************
    IPOL: INPUT POLARITY PORT REGISTER (ADDR 0x01)
**************************************************************************/
/*
bit 7-0         IP<7:0>: Controls the polarity inversion of the input pins <7:0>
                1 = GPIO register bit reflects the opposite logic state of the input pin.
                0 = GPIO register bit reflects the same logic state of the input pin.
*/

#define IPOL_REGISTER 0x01

/**************************************************************************
    GPINTEN: INTERRUPT-ON-CHANGE PINS (ADDR 0x02) (Note 1)
**************************************************************************/
/*
bit 7-0         GPINT<7:0>: General purpose I/O interrupt-on-change bits <7:0>
                1 = Enables GPIO input pin for interrupt-on-change event.
                0 = Disables GPIO input pin for interrupt-on-change event.

                Note 1: Refer to INTCON.
*/

#define GPINT_REGISTER 0x02


/**************************************************************************
    DEFVAL: DEFAULT VALUE REGISTER (ADDR 0x03)
**************************************************************************/
/*
bit 7-0         DEFVAL<7:0>: Sets the compare value for pins configured for
                interrupt-on-change from defaults <7:0> (Note 1)

                If the associated pin level is the opposite from the register bit,
                an interrupt occurs. (Note 2)

                Note 1: Refer to INTCON.
                     2: Refer to INTCON and GPINTEN.
*/

#define DEFVAL_REGISTER 0x03


/**************************************************************************
    INTCON: INTERRUPT-ON-CHANGE CONTROL REGISTER (ADDR 0x04) (Note 1)
**************************************************************************/
/*
bit 7-0         IOC<7:0>: Controls how the associated pin value is compared for interrupt-on-change <7:0>
                1 = Pin value is compared against the associated bit in the DEFVAL register.
                0 = Pin value is compared against the previous pin value.

                Note 1: Refer to INTCON and GPINTEN.
*/

#define INTCON_REGISTER 0x04

/**************************************************************************
    IOCON: I/O EXPANDER CONFIGURATION REGISTER (ADDR 0x05)
**************************************************************************/

/*
bit 7 BANK:     Controls how the registers are addressed
                1 = The registers associated with each port are separated into different banks.
                0 = The registers are in the same bank (addresses are sequential).

bit 6 MIRROR:   INT Pins Mirror bit
                1 = The INT pins are internally connected
                0 = The INT pins are not connected. INTA is associated with PORTA and INTB is associated with
                    PORTB

bit 5 SEQOP:    Sequential Operation mode bit
                1 = Sequential operation disabled, address pointer does not increment.
                0 = Sequential operation enabled, address pointer increments.

bit 4 DISSLW:   Slew Rate control bit for SDA output
                1 = Slew rate disabled
                0 = Slew rate enabled

bit 3 HAEN:     Hardware Address Enable bit (MCP23S17 only) (Note 1)
                1 = Enables the MCP23S17 address pins.
                0 = Disables the MCP23S17 address pins.

bit 2 ODR:      Configures the INT pin as an open-drain output
                1 = Open-drain output (overrides the INTPOL bit.)
                0 = Active driver output (INTPOL bit sets the polarity.)

bit 1 INTPOL:   This bit sets the polarity of the INT output pin
                1 = Active-high
                0 = Active-low

bit 0 Unimplemented: Read as ‘0’
*/
#define IOCON_7_BANK        0x80
#define IOCON_6_MIRROR		0x40
#define IOCON_5_SEQOP		0x20
#define IOCON_4_IPOLB		0x10
#define IOCON_3_HAEN        0x08
#define IOCON_2_ODR         0x04
#define IOCON_1_INTPOL		0x02
#define IOCON_0_NOTUSED		0x01

#define IOCON_REGISTER 0x05

/**************************************************************************
    GPPU: GPIO PULL-UP RESISTOR REGISTER (ADDR 0x06)
**************************************************************************/
/*
bit 7-0         PU<7:0> Controls the weak pull-up resistors on each pin (when configured as an input)
                1 = Pull-up enabled
                0 = Pull-up disabled
*/

#define GPPU_REGISTER 0x06

/**************************************************************************
    INTF: INTERRUPT FLAG REGISTER (ADDR 0x07)
**************************************************************************/
/*
bit 7-0 INT<7:0>:           Reflects the interrupt condition on the port. It reflects the change only if interrupts are
                            enabled per GPINTEN<7:0>.
                            1 = Pin caused interrupt.
                            0 = Interrupt not pending
*/

#define INTF_REGISTER 0x07

/**************************************************************************
    INTCAP: INTERRUPT CAPTURED VALUE FOR PORT REGISTER (ADDR 0x08)
**************************************************************************/
/*
bit 7-0                 ICP<7:0>: Reflects the logic level on the port pins at the time of interrupt due to pin change <7:0>
                        1 = Logic-high
                        0 = Logic-low
*/

#define INTCAP_REGISTER 0x08

/**************************************************************************
    GPIO: GENERAL PURPOSE I/O PORT REGISTER (ADDR 0x09)
**************************************************************************/
/*
bit 7-0 GP<7:0>:        Reflects the logic level on the pins <7:0>
                        1 = Logic-high
                        0 = Logic-low
*/

#define GPIO_REGISTER 0x09

/**************************************************************************
    OLAT: OUTPUT LATCH REGISTER 0 (ADDR 0x0A)
**************************************************************************/
/*
bit 7-0 OL<7:0>:        Reflects the logic level on the output latch <7:0>
                        1 = Logic-high
                        0 = Logic-low
*/

#define OLAT_REGISTER 0x0A

/**************************************************************************
    REGISTERS GPIO STATE
**************************************************************************/
#define GPIO_ALL_OUTPUT     0x0000
#define GPIO_ALL_INPUT      0xFFFF
#define GPIO_ALL_OFF        0x0000
#define GPIO_ALL_ON         0xFFFF
#define GPIO_HIGH           1
#define GPIO_LOW            0

#define MCP23017_INTERRUPT_SUPPORT 0 //< Enables support for MCP23017 interrupts.

#include <QtGlobal>
#include <QDebug>

#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <mcp23017.h>

#include <globalenumerate.h>

/*!
* \  smcp23017_device
* @brief 23017_device device
*
*/
typedef struct
{
    quint8 chip_id;         /*! Chip Id */
    quint8 device_id;       /*! Device Id */
    quint16 IODIR_reg;       /*! Device IODIR register */
    quint16 IPOL_reg;        /*! Device IPO register */
    quint16 GPINT_reg;       /*! Device GPINT register */
    quint16 DEFVAL_reg;      /*! Device DEFVAL register */
    quint16 INTCON_reg;      /*! Device INTCON register */
    quint16 IOCON_reg;      /*! Device IOCON register */
    quint16 GPPU_reg;    /*! Device GPPU register */
    quint16 INTF_reg;    /*! Device INTF register */
    quint16 INTCAP_reg;    /*! Device INTCAP register */
    quint16 GPIO_reg;    /*! Device GPIO register */
    quint16 OLAT_reg;    /*! Device OLAT register */
}smcp23017_device, *pmcp23017_device;

/*!
* \  smcp23017_device
* @brief 23017_device device
*
*/
typedef struct
{
    quint8 BANK;            /*! sequential register addresses */
    quint8 MIRROR;          /*! use configureInterrupt */
    quint8 SEQOP;           /*! sequential operation disabled, address pointer does not increment */
    quint8 DISSLW;          /*! slew rate enabled */
    quint8 HAEN;            /*! hardware address pin is always enabled on 23017 */
    quint8 ODR;             /*! open drain output */
    quint8 INTPOL;          /*! interrupt active low */
    quint8 NOTUSED;         /*! first bite not used*/
}smcp23017_IOCON, *pmcp23017_IOCON;

class MCP23017
{
public:
    MCP23017(quint8 device_I2C_Adress = MCP23017_ADDRESS_DEFAULT_20, quint8 pinbase = 65, quint8 fd = 0);

    /**
     * Initializes the device structure register all to 0
     */
    void init_smcp23017_device(pmcp23017_device pmcp23017_device);

    /**
     * Initializes the IOCON structure all to 0
     */
    void init_smcp23017_IOCON(pmcp23017_IOCON pmcp23017_IOCONreg);

//    /**
//     * Initializes the chip with the default configuration.
//     * Enables Byte mode (IOCON.BANK = 0 and IOCON.SEQOP = 1).
//     * Enables pull-up resistors for all pins. This will only be effective for input pins.
//     *
//     * See "3.2.1 Byte mode and Sequential mode".
//     */
//    void init();

    /**
     * Controls the pins direction on a whole port at once.
     *
     * 1 = Pin is configured as an input.
     * 0 = Pin is configured as an output.
     *
     * See "3.5.1 I/O Direction register".
     */
    void writeGPIOPinMode();

    /**
     * Controls a single pin direction.
     * Pin 0-7 for port A, 8-15 fo port B.
     *
     * 1 = Pin is configured as an input.
     * 0 = Pin is configured as an output.
     *
     * See "3.5.1 I/O Direction register".
     */
    void gpioSinglePinModeDirection(quint8 pin, bool direction);

    /**
     * Writes a single pin state.
     * Pin 0-7 for port A, 8-15 for port B.
     *
     * 1 = Logic-high
     * 0 = Logic-low
     *
     * See "3.5.10 Port register".
     */
    void gpioPinDigitalWrite(quint8 pin, bool value);

    /**
     * Reads a single pin state.
     * Pin 0-7 for port A, 8-15 for port B.
     *
     * 1 = Logic-high
     * 0 = Logic-low
     *
     * See "3.5.10 Port register".
     */
    bool gpioPinDigitalRead(quint8 pin);


    /**
     * Reads all pin state.
     * Pin 0-7 for port A, 8-15 for port B.
     *
     * 1 = Logic-high
     * 0 = Logic-low
     *
     * See "3.5.10 Port register".
     */
    void gpioPinWriteAll(quint16 allPinValue);


    /**
     * Reads all pin state.
     * Pin 0-7 for port A, 8-15 for port B.
     *
     * 1 = Logic-high
     * 0 = Logic-low
     *
     * See "3.5.10 Port register".
     */
    quint16 gpioPinReadAll();


    /**
     * Writes a register value.
     */
    void writeRegister16(quint8 registerName, quint16 value);
    void writeRegister8(quint8 registerName, quint8 value);

    /**
     * Reads a register value.
     */
    quint8 readRegister8(quint8 registerName);

    quint16 readRegister16(quint16 registerName);

#if MCP23017_INTERRUPT_SUPPORT

    /**
     * Controls how the interrupt pins act with each other.
     * If intMode is SEPARATED, interrupt conditions on a port will cause its respective INT pin to active.
     * If intMode is OR, interrupt pins are OR'ed so an interrupt on one of the port will cause both pints to active.
     *
     * Controls the IOCON.MIRROR bit.
     * See "3.5.6 Configuration register".
     */
    void interruptMode(MCP23017_INTMODE intMode);
    /**
     * Configures interrupt registers using an Arduino-like API.
     * mode can be one of CHANGE, FALLING or RISING.
     */
    void interrupt(MCP23017_PORT port, uint8_t mode);
    /**
     * Disable interrupts for the specified port.
     */
    void disableInterrupt(MCP23017_PORT port);
    /**
     * Reads which pin caused the interrupt.
     */
    void interruptedBy(uint8_t& portA, uint8_t& portB);
    /**
     * Clears interrupts on both ports.
     */
    void clearInterrupts();
    /**
     * Clear interrupts on both ports. Returns port values at the time the interrupt occured.
     */
    void clearInterrupts(uint8_t& portA, uint8_t& portB);

#endif
    quint8 MCP23017_IOCON() const;
    void setMCP23017_IOCON(const quint8 &MCP23017_IOCON);


    quint8 MCP23017_fd() const;

    pmcp23017_device pdevice() const;
    void setPdevice(const pmcp23017_device &pdevice);

//    pmcp23017_IOCON pIOCON() const;
//    void setPIOCON(const pmcp23017_IOCON &pIOCON);

    quint16 convertIOCONStructToRegValue(pmcp23017_IOCON pIOCON);

    quint16 gpioDirection() const;
    void setGpioDirection(const quint16 &gpioDirection);

private:
    quint8 _MCP23017_i2cAddress;
    quint8 _MCP23017_pinBase;
    quint8 _MCP23017_fd;
    quint8 _MCP23017_IOCON;
    pmcp23017_device _pdevice;
//    pmcp23017_IOCON _pIOCON;
    quint16 _gpioDirection;
    quint16	_gpioState;

};

#endif // MCP23017_H
