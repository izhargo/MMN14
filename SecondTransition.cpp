#include "SharedHeaderFile.h"
#include "SecondTransitionHeader.h"

/*A function to add to the memory a mov command with two registers as its parameter*/
void movTwoRegisterCmd(parms data)
{
	commandBitField newMovCommand;
	registersParam newRegistersParam;

	newMovCommand.fullCommandInt = 0;
	newMovCommand.cBitField.encodingType = External;
	newMovCommand.cBitField.sourceOperandAddressing = DirectRegister;
	newMovCommand.cBitField.destinationOperandAddressing = DirectRegister;
	newMovCommand.cBitField.opcode = opcodesArray[0].opcodeNum;

	cpuFullMemory[IC].fullReg = newMovCommand.fullCommandInt;
	IC++;

	data.regDestination->r.reg = data.regSource->r.reg;

	newRegistersParam.fullRegParam = 0;
	newRegistersParam.regParam.encodingType = External;
	newRegistersParam.regParam.regSource = data.eRegSource;
	newRegistersParam.regParam.regDestination = data.eRegDestination;

	cpuFullMemory[IC].fullReg = newRegistersParam.fullRegParam;
	IC++;
}

/*A function to add to the memory a mov command with a register and a numeric value as its parameter*/
void movRegisterValueCmd(parms data)
{
	commandBitField newMovCommand;
	registersParam newRegistersParam;
	valueParam newValueParam;

	newMovCommand.fullCommandInt = 0;
	newMovCommand.cBitField.encodingType = External;
	newMovCommand.cBitField.sourceOperandAddressing = Immediate;
	newMovCommand.cBitField.destinationOperandAddressing = DirectRegister;
	newMovCommand.cBitField.opcode = opcodesArray[0].opcodeNum;

	cpuFullMemory[IC].fullReg = newMovCommand.fullCommandInt;
	IC++;

	newValueParam.fullValueParam = 0;
	newValueParam.valParam.encodingType = Absolute;
	newValueParam.valParam.numericValue = data.sourceNum;

	cpuFullMemory[IC].fullReg = newValueParam.fullValueParam;
	IC++;

	data.regDestination->r.reg = data.sourceNum;

	newRegistersParam.fullRegParam = 0;
	newRegistersParam.regParam.encodingType = External;
	newRegistersParam.regParam.regDestination = data.eRegDestination;

	cpuFullMemory[IC].fullReg = newRegistersParam.fullRegParam;
	IC++;
}

/*A function to add to the memory a cmp command with two registers as its parameter*/
void cmpTwoRegisterCmd(parms data)
{
	commandBitField newCmpCommand;
	registersParam newRegistersParam;

	newCmpCommand.fullCommandInt = 0;
	newCmpCommand.cBitField.encodingType = External;
	newCmpCommand.cBitField.sourceOperandAddressing = DirectRegister;
	newCmpCommand.cBitField.destinationOperandAddressing = DirectRegister;
	newCmpCommand.cBitField.opcode = opcodesArray[1].opcodeNum;

	cpuFullMemory[IC].fullReg = newCmpCommand.fullCommandInt;
	IC++;

	newRegistersParam.fullRegParam = 0;
	newRegistersParam.regParam.encodingType = External;
	newRegistersParam.regParam.regSource = data.eRegSource;
	newRegistersParam.regParam.regDestination = data.eRegDestination;

	cpuFullMemory[IC].fullReg = newRegistersParam.fullRegParam;
	IC++;
}

/*A function to add to the memory a cmp command with a register and a numeric value as its parameter*/
void cmpRegisterValueCmd(parms data)
{
	commandBitField newCmpCommand;
	registersParam newRegistersParam;
	valueParam newValueParam;

	newCmpCommand.fullCommandInt = 0;
	newCmpCommand.cBitField.encodingType = External;
	newCmpCommand.cBitField.sourceOperandAddressing = Immediate;
	newCmpCommand.cBitField.destinationOperandAddressing = DirectRegister;
	newCmpCommand.cBitField.opcode = opcodesArray[1].opcodeNum;

	cpuFullMemory[IC].fullReg = newCmpCommand.fullCommandInt;
	IC++;

	newValueParam.fullValueParam = 0;
	newValueParam.valParam.encodingType = Absolute;
	newValueParam.valParam.numericValue = data.sourceNum;

	cpuFullMemory[IC].fullReg = newValueParam.fullValueParam;
	IC++;

	newRegistersParam.fullRegParam = 0;
	newRegistersParam.regParam.encodingType = External;
	newRegistersParam.regParam.regDestination = data.eRegDestination;

	cpuFullMemory[IC].fullReg = newRegistersParam.fullRegParam;
	IC++;
}

/*A function to add to the memory a add command with two registers as its parameter*/
void addTwoRegisterCmd(parms data)
{
	commandBitField newAddCommand;
	registersParam newRegistersParam;

	newAddCommand.fullCommandInt = 0;
	newAddCommand.cBitField.encodingType = External;
	newAddCommand.cBitField.sourceOperandAddressing = DirectRegister;
	newAddCommand.cBitField.destinationOperandAddressing = DirectRegister;
	newAddCommand.cBitField.opcode = opcodesArray[2].opcodeNum;

	cpuFullMemory[IC].fullReg = newAddCommand.fullCommandInt;
	IC++;

	data.regDestination->r.reg += data.regSource->r.reg;

	newRegistersParam.fullRegParam = 0;
	newRegistersParam.regParam.encodingType = External;
	newRegistersParam.regParam.regSource = data.eRegSource;
	newRegistersParam.regParam.regDestination = data.eRegDestination;

	cpuFullMemory[IC].fullReg = newRegistersParam.fullRegParam;
	IC++;
}

/*A function to add to the memory a add command with a register and a numeric value as its parameter*/
void addRegisterValueCmd(parms data)
{
	commandBitField newAddCommand;
	registersParam newRegistersParam;
	valueParam newValueParam;

	newAddCommand.fullCommandInt = 0;
	newAddCommand.cBitField.encodingType = External;
	newAddCommand.cBitField.sourceOperandAddressing = Immediate;
	newAddCommand.cBitField.destinationOperandAddressing = DirectRegister;
	newAddCommand.cBitField.opcode = opcodesArray[2].opcodeNum;

	cpuFullMemory[IC].fullReg = newAddCommand.fullCommandInt;
	IC++;

	newValueParam.fullValueParam = 0;
	newValueParam.valParam.encodingType = Absolute;
	newValueParam.valParam.numericValue = data.sourceNum;

	cpuFullMemory[IC].fullReg = newValueParam.fullValueParam;
	IC++;

	data.regDestination->r.reg += data.sourceNum;

	newRegistersParam.fullRegParam = 0;
	newRegistersParam.regParam.encodingType = External;
	newRegistersParam.regParam.regDestination = data.eRegDestination;

	cpuFullMemory[IC].fullReg = newRegistersParam.fullRegParam;
	IC++;
}

/*A function to add to the memory a sub command with two registers as its parameter*/
void subTwoRegisterCmd(parms data)
{
	commandBitField newSubCommand;
	registersParam newRegistersParam;

	newSubCommand.fullCommandInt = 0;
	newSubCommand.cBitField.encodingType = External;
	newSubCommand.cBitField.sourceOperandAddressing = DirectRegister;
	newSubCommand.cBitField.destinationOperandAddressing = DirectRegister;
	newSubCommand.cBitField.opcode = opcodesArray[3].opcodeNum;

	cpuFullMemory[IC].fullReg = newSubCommand.fullCommandInt;
	IC++;

	data.regDestination->r.reg -= data.regSource->r.reg;

	newRegistersParam.fullRegParam = 0;
	newRegistersParam.regParam.encodingType = External;
	newRegistersParam.regParam.regSource = data.eRegSource;
	newRegistersParam.regParam.regDestination = data.eRegDestination;

	cpuFullMemory[IC].fullReg = newRegistersParam.fullRegParam;
	IC++;
}

/*A function to add to the memory a sub command with a register and a numeric value as its parameter*/
void subRegisterValueCmd(parms data)
{
	commandBitField newSubCommand;
	registersParam newRegistersParam;
	valueParam newValueParam;

	newSubCommand.fullCommandInt = 0;
	newSubCommand.cBitField.encodingType = External;
	newSubCommand.cBitField.sourceOperandAddressing = Immediate;
	newSubCommand.cBitField.destinationOperandAddressing = DirectRegister;
	newSubCommand.cBitField.opcode = opcodesArray[3].opcodeNum;

	cpuFullMemory[IC].fullReg = newSubCommand.fullCommandInt;
	IC++;

	newValueParam.fullValueParam = 0;
	newValueParam.valParam.encodingType = Absolute;
	newValueParam.valParam.numericValue = data.sourceNum;

	cpuFullMemory[IC].fullReg = newValueParam.fullValueParam;
	IC++;

	data.regDestination->r.reg -= data.sourceNum;

	newRegistersParam.fullRegParam = 0;
	newRegistersParam.regParam.encodingType = External;
	newRegistersParam.regParam.regDestination = data.eRegDestination;

	cpuFullMemory[IC].fullReg = newRegistersParam.fullRegParam;
	IC++;
}

/*A function to add to the memory a lea command with two registers as its parameter*/
void leaTwoRegisterCmd(parms data)
{
	commandBitField newLeaCommand;
	registersParam newRegistersParam;

	newLeaCommand.fullCommandInt = 0;
	newLeaCommand.cBitField.encodingType = External;
	newLeaCommand.cBitField.sourceOperandAddressing = DirectRegister;
	newLeaCommand.cBitField.destinationOperandAddressing = DirectRegister;
	newLeaCommand.cBitField.opcode = opcodesArray[6].opcodeNum;

	cpuFullMemory[IC].fullReg = newLeaCommand.fullCommandInt;
	IC++;

	data.regDestination->r.reg += data.regSource->r.reg;

	newRegistersParam.fullRegParam = 0;
	newRegistersParam.regParam.encodingType = External;
	newRegistersParam.regParam.regSource = data.eRegSource;
	newRegistersParam.regParam.regDestination = data.eRegDestination;

	cpuFullMemory[IC].fullReg = newRegistersParam.fullRegParam;
	IC++;
}

/*A function to add to the memory a lea command with a register and a numeric value as its parameter*/
void leaRegisterValueCmd(parms data)
{
	commandBitField newLeaCommand;
	registersParam newRegistersParam;
	valueParam newValueParam;

	newLeaCommand.fullCommandInt = 0;
	newLeaCommand.cBitField.encodingType = External;
	newLeaCommand.cBitField.sourceOperandAddressing = Immediate;
	newLeaCommand.cBitField.destinationOperandAddressing = DirectRegister;
	newLeaCommand.cBitField.opcode = opcodesArray[6].opcodeNum;

	cpuFullMemory[IC].fullReg = newLeaCommand.fullCommandInt;
	IC++;

	newValueParam.fullValueParam = 0;
	newValueParam.valParam.encodingType = Absolute;
	newValueParam.valParam.numericValue = data.sourceNum;

	cpuFullMemory[IC].fullReg = newValueParam.fullValueParam;
	IC++;

	newRegistersParam.fullRegParam = 0;
	newRegistersParam.regParam.encodingType = External;
	newRegistersParam.regParam.regDestination = data.eRegDestination;

	cpuFullMemory[IC].fullReg = newRegistersParam.fullRegParam;
	IC++;
}

/*A function to add to the memory a not command with a register as its parameter*/
void notRegisterCmd(parms data)
{
	commandBitField newNotCommand;
	registersParam newRegistersParam;

	newNotCommand.fullCommandInt = 0;
	newNotCommand.cBitField.encodingType = External;
	newNotCommand.cBitField.destinationOperandAddressing = DirectRegister;
	newNotCommand.cBitField.opcode = opcodesArray[4].opcodeNum;

	cpuFullMemory[IC].fullReg = newNotCommand.fullCommandInt;
	IC++;

	data.regDestination->r.reg = ~(data.regDestination->r.reg);

	newRegistersParam.fullRegParam = 0;
	newRegistersParam.regParam.encodingType = External;
	newRegistersParam.regParam.regDestination = data.eRegDestination;

	cpuFullMemory[IC].fullReg = newRegistersParam.fullRegParam;
	IC++;
}

/*A function to add to the memory a clr command with a register as its parameter*/
void clrRegisterCmd(parms data)
{
	commandBitField newClrCommand;
	registersParam newRegistersParam;

	newClrCommand.fullCommandInt = 0;
	newClrCommand.cBitField.encodingType = External;
	newClrCommand.cBitField.destinationOperandAddressing = DirectRegister;
	newClrCommand.cBitField.opcode = opcodesArray[5].opcodeNum;

	cpuFullMemory[IC].fullReg = newClrCommand.fullCommandInt;
	IC++;

	data.regDestination->r.reg = 0;

	newRegistersParam.fullRegParam = 0;
	newRegistersParam.regParam.encodingType = External;
	newRegistersParam.regParam.regDestination = data.eRegDestination;

	cpuFullMemory[IC].fullReg = newRegistersParam.fullRegParam;
	IC++;
}

/*A function to add to the memory an inc command with a register as its parameter*/
void incRegisterCmd(parms data)
{
	commandBitField newIncCommand;
	registersParam newRegistersParam;

	newIncCommand.fullCommandInt = 0;
	newIncCommand.cBitField.encodingType = External;
	newIncCommand.cBitField.destinationOperandAddressing = DirectRegister;
	newIncCommand.cBitField.opcode = opcodesArray[7].opcodeNum;

	cpuFullMemory[IC].fullReg = newIncCommand.fullCommandInt;
	IC++;

	data.regDestination->r.reg += 1;

	newRegistersParam.fullRegParam = 0;
	newRegistersParam.regParam.encodingType = External;
	newRegistersParam.regParam.regDestination = data.eRegDestination;

	cpuFullMemory[IC].fullReg = newRegistersParam.fullRegParam;
	IC++;
}

/*A function to add to the memory a dec command with a register as its parameter*/
void decRegisterCmd(parms data)
{
	commandBitField newDecCommand;
	registersParam newRegistersParam;

	newDecCommand.fullCommandInt = 0;
	newDecCommand.cBitField.encodingType = External;
	newDecCommand.cBitField.destinationOperandAddressing = DirectRegister;
	newDecCommand.cBitField.opcode = opcodesArray[8].opcodeNum;

	cpuFullMemory[IC].fullReg = newDecCommand.fullCommandInt;
	IC++;

	data.regDestination->r.reg -= 1;

	newRegistersParam.fullRegParam = 0;
	newRegistersParam.regParam.encodingType = External;
	newRegistersParam.regParam.regDestination = data.eRegDestination;

	cpuFullMemory[IC].fullReg = newRegistersParam.fullRegParam;
	IC++;
}

/*A function to add to the memory a jmp command with a register as its parameter*/
void jmpRegisterCmd(parms data)
{
	commandBitField newJmpCommand;
	registersParam newRegistersParam;

	newJmpCommand.fullCommandInt = 0;
	newJmpCommand.cBitField.encodingType = External;
	newJmpCommand.cBitField.destinationOperandAddressing = DirectRegister;
	newJmpCommand.cBitField.opcode = opcodesArray[9].opcodeNum;

	cpuFullMemory[IC].fullReg = newJmpCommand.fullCommandInt;
	IC++;

	newRegistersParam.fullRegParam = 0;
	newRegistersParam.regParam.encodingType = External;
	newRegistersParam.regParam.regDestination = data.eRegDestination;

	cpuFullMemory[IC].fullReg = newRegistersParam.fullRegParam;
	IC++;
}

/*A function to add to the memory a bne command with a register as its parameter*/
void bneRegisterCmd(parms data)
{
	commandBitField newBneCommand;
	registersParam newRegistersParam;

	newBneCommand.fullCommandInt = 0;
	newBneCommand.cBitField.encodingType = External;
	newBneCommand.cBitField.destinationOperandAddressing = DirectRegister;
	newBneCommand.cBitField.opcode = opcodesArray[10].opcodeNum;

	cpuFullMemory[IC].fullReg = newBneCommand.fullCommandInt;
	IC++;

	newRegistersParam.fullRegParam = 0;
	newRegistersParam.regParam.encodingType = External;
	newRegistersParam.regParam.regDestination = data.eRegDestination;

	cpuFullMemory[IC].fullReg = newRegistersParam.fullRegParam;
	IC++;
}

/*A function to add to the memory a red command with a register as its parameter*/
void redRegisterCmd(parms data)
{
	commandBitField newRedCommand;
	registersParam newRegistersParam;

	newRedCommand.fullCommandInt = 0;
	newRedCommand.cBitField.encodingType = External;
	newRedCommand.cBitField.destinationOperandAddressing = DirectRegister;
	newRedCommand.cBitField.opcode = opcodesArray[11].opcodeNum;

	cpuFullMemory[IC].fullReg = newRedCommand.fullCommandInt;
	IC++;

	newRegistersParam.fullRegParam = 0;
	newRegistersParam.regParam.encodingType = External;
	newRegistersParam.regParam.regDestination = data.eRegDestination;

	cpuFullMemory[IC].fullReg = newRegistersParam.fullRegParam;
	IC++;
}

/*A function to add to the memory a prn command with a register as its parameter*/
void prnRegisterCmd(parms data)
{
	commandBitField newPrnCommand;
	registersParam newRegistersParam;

	newPrnCommand.fullCommandInt = 0;
	newPrnCommand.cBitField.encodingType = External;
	newPrnCommand.cBitField.destinationOperandAddressing = DirectRegister;
	newPrnCommand.cBitField.opcode = opcodesArray[12].opcodeNum;

	cpuFullMemory[IC].fullReg = newPrnCommand.fullCommandInt;
	IC++;

	newRegistersParam.fullRegParam = 0;
	newRegistersParam.regParam.encodingType = External;
	newRegistersParam.regParam.regDestination = data.eRegDestination;

	cpuFullMemory[IC].fullReg = newRegistersParam.fullRegParam;
	IC++;
}

/*A function to add to the memory a jsr command with a register as its parameter*/
void jsrRegisterCmd(parms data)
{
	commandBitField newJsrCommand;
	registersParam newRegistersParam;

	newJsrCommand.fullCommandInt = 0;
	newJsrCommand.cBitField.encodingType = External;
	newJsrCommand.cBitField.destinationOperandAddressing = DirectRegister;
	newJsrCommand.cBitField.opcode = opcodesArray[13].opcodeNum;

	cpuFullMemory[IC].fullReg = newJsrCommand.fullCommandInt;
	IC++;

	newRegistersParam.fullRegParam = 0;
	newRegistersParam.regParam.encodingType = External;
	newRegistersParam.regParam.regDestination = data.eRegDestination;

	cpuFullMemory[IC].fullReg = newRegistersParam.fullRegParam;
	IC++;
}

/*A function to add to the memory a rts command*/
void rtsCmd(parms data)
{
	commandBitField newRtsCommand;
	registersParam newRegistersParam;

	newRtsCommand.fullCommandInt = 0;
	newRtsCommand.cBitField.encodingType = Absolute;
	newRtsCommand.cBitField.opcode = opcodesArray[14].opcodeNum;

	cpuFullMemory[IC].fullReg = newRtsCommand.fullCommandInt;
	IC++;
}

/*A function to add to the memory a stop command*/
void StopCmd(parms data)
{
	commandBitField newRtsCommand;
	registersParam newRegistersParam;

	newRtsCommand.fullCommandInt = 0;
	newRtsCommand.cBitField.encodingType = Absolute;
	newRtsCommand.cBitField.opcode = opcodesArray[15].opcodeNum;

	cpuFullMemory[IC].fullReg = newRtsCommand.fullCommandInt;
	IC++;
}

