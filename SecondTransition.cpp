#include "SharedHeaderFile.h"
#include "SecondTransitionHeader.h"

/*A function to add to the memory a mov command with two registers as its parameter*/
void movTwoRegister(parms data)
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