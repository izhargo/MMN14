#include "SharedHeaderFile.h"
#include "SecondTransitionHeader.h"

/*A function to readdress all the symbols address in the symbol table*/
void readdressSymbolTable()
{
	pSymbol current = SymbolTable;
	while(current)
	{
		if(current->external == 0 && current->action == 0)
		{
			current->addresse += IC;
		}
		current = current->next;
	}
}

/*A function to add to the memory a mov command with a register as its source parameter and a register as its destination parameter*/
void movTwoRegisterCmd(parms data)
{
	commandBitField newMovCommand;
	registersParam srcDstRegistersParam;

	newMovCommand.fullCommandInt = 0;
	newMovCommand.cBitField.encodingType = External;
	newMovCommand.cBitField.sourceOperandAddressing = DirectRegister;
	newMovCommand.cBitField.destinationOperandAddressing = DirectRegister;
	newMovCommand.cBitField.opcode = opcodesArray[0].opcodeNum;

	cpuFullMemory[IC].fullReg = newMovCommand.fullCommandInt;
	IC++;

	srcDstRegistersParam.fullRegParam = 0;
	srcDstRegistersParam.regParam.encodingType = External;
	srcDstRegistersParam.regParam.regSource = data.eRegSource;
	srcDstRegistersParam.regParam.regDestination = data.eRegDestination;

	cpuFullMemory[IC].fullReg = srcDstRegistersParam.fullRegParam;
	IC++;
}

/*A function to add to the memory a mov command with a register as its source parameter and a symbol parameter as its destination parameter*/
void movRegisterSymbolCmd(parms data)
{
	commandBitField newMovCommand;
	registersParam sourceRegisterParam;
	symbolParam destinationSymbolParam;

	newMovCommand.fullCommandInt = 0;
	if(data.symbolDestination->external)
		newMovCommand.cBitField.encodingType = External;
	else
		newMovCommand.cBitField.encodingType = Relocatable;
	newMovCommand.cBitField.sourceOperandAddressing = DirectRegister;
	newMovCommand.cBitField.destinationOperandAddressing = Direct;
	newMovCommand.cBitField.opcode = opcodesArray[0].opcodeNum;

	cpuFullMemory[IC].fullReg = newMovCommand.fullCommandInt;
	IC++;

	sourceRegisterParam.fullRegParam = 0;
	sourceRegisterParam.regParam.encodingType = External;
	sourceRegisterParam.regParam.regSource = data.eRegSource;

	cpuFullMemory[IC].fullReg = sourceRegisterParam.fullRegParam;
	IC++;

	destinationSymbolParam.fullSymbolParam = 0;
	destinationSymbolParam.symParam.encodingType = Relocatable;
	destinationSymbolParam.symParam.addressValue = data.symbolDestination->addresse;

	cpuFullMemory[IC].fullReg = destinationSymbolParam.fullSymbolParam;
	IC++;
}

/*A function to add to the memory a mov command with a symbol paramater as its source parameter and a register as its destination parameter*/
void movSymbolRegisterCmd(parms data)
{
	commandBitField newMovCommand;
	symbolParam sourceSymbolParam;
	registersParam destinationRegisterParam;

	newMovCommand.fullCommandInt = 0;
	newMovCommand.cBitField.encodingType = External;
	newMovCommand.cBitField.sourceOperandAddressing = Direct;
	newMovCommand.cBitField.destinationOperandAddressing = DirectRegister;
	newMovCommand.cBitField.opcode = opcodesArray[0].opcodeNum;

	cpuFullMemory[IC].fullReg = newMovCommand.fullCommandInt;
	IC++;

	sourceSymbolParam.fullSymbolParam = 0;
	sourceSymbolParam.symParam.encodingType = Relocatable;
	sourceSymbolParam.symParam.addressValue = data.symbolSource->addresse;

	cpuFullMemory[IC].fullReg = sourceSymbolParam.fullSymbolParam;
	IC++;
	
	destinationRegisterParam.fullRegParam = 0;
	destinationRegisterParam.regParam.encodingType = External;
	destinationRegisterParam.regParam.regDestination = data.eRegDestination;

	cpuFullMemory[IC].fullReg = destinationRegisterParam.fullRegParam;
	IC++;
}

/*A function to add to the memory a mov command a two symbol paramater as its source parameter and a symbol parameter as its destination parameter*/
void movSymbolSymbolCmd(parms data)
{
	commandBitField newMovCommand;
	symbolParam SourceSymbolParam;
	symbolParam DesinationSymbolParam;

	newMovCommand.fullCommandInt = 0;
	if(data.symbolDestination->external)
		newMovCommand.cBitField.encodingType = External;
	else
		newMovCommand.cBitField.encodingType = Relocatable;
	newMovCommand.cBitField.sourceOperandAddressing = Direct;
	newMovCommand.cBitField.destinationOperandAddressing = DirectRegister;
	newMovCommand.cBitField.opcode = opcodesArray[0].opcodeNum;

	cpuFullMemory[IC].fullReg = newMovCommand.fullCommandInt;
	IC++;

	SourceSymbolParam.fullSymbolParam = 0;
	SourceSymbolParam.symParam.encodingType = Relocatable;
	SourceSymbolParam.symParam.addressValue = data.symbolSource->addresse;

	cpuFullMemory[IC].fullReg = SourceSymbolParam.fullSymbolParam;
	IC++;
	
	DesinationSymbolParam.fullSymbolParam = 0;
	DesinationSymbolParam.symParam.encodingType = External;
	DesinationSymbolParam.symParam.addressValue = data.symbolDestination->addresse;

	cpuFullMemory[IC].fullReg = DesinationSymbolParam.fullSymbolParam;
	IC++;
}

/*A function to add to the memory a mov command with a numeric value as its source parameter and a register as its destination parameter*/
void movValueRegisterCmd(parms data)
{
	commandBitField newMovCommand;
	valueParam sourceValueParam;
	registersParam destinationRegisterParam;

	newMovCommand.fullCommandInt = 0;
	newMovCommand.cBitField.encodingType = External;
	newMovCommand.cBitField.sourceOperandAddressing = Immediate;
	newMovCommand.cBitField.destinationOperandAddressing = DirectRegister;
	newMovCommand.cBitField.opcode = opcodesArray[0].opcodeNum;

	cpuFullMemory[IC].fullReg = newMovCommand.fullCommandInt;
	IC++;

	sourceValueParam.fullValueParam = 0;
	sourceValueParam.valParam.encodingType = Absolute;
	sourceValueParam.valParam.numericValue = data.sourceNum;

	cpuFullMemory[IC].fullReg = sourceValueParam.fullValueParam;
	IC++;

	destinationRegisterParam.fullRegParam = 0;
	destinationRegisterParam.regParam.encodingType = External;
	destinationRegisterParam.regParam.regDestination = data.eRegDestination;

	cpuFullMemory[IC].fullReg = destinationRegisterParam.fullRegParam;
	IC++;
}

/*A function to add to the memory a mov command with a numeric value as its source parameter and a symbol parameter as its destination parameter*/
void movValueSymbolCmd(parms data)
{
	commandBitField newMovCommand;
	valueParam sourceValueParam;
	symbolParam DesinationSymbolParam;

	newMovCommand.fullCommandInt = 0;
	if(data.symbolDestination->external)
		newMovCommand.cBitField.encodingType = External;
	else
		newMovCommand.cBitField.encodingType = Relocatable;
	newMovCommand.cBitField.sourceOperandAddressing = Direct;
	newMovCommand.cBitField.destinationOperandAddressing = DirectRegister;
	newMovCommand.cBitField.opcode = opcodesArray[0].opcodeNum;

	cpuFullMemory[IC].fullReg = newMovCommand.fullCommandInt;
	IC++;

	sourceValueParam.fullValueParam = 0;
	sourceValueParam.valParam.encodingType = Absolute;
	sourceValueParam.valParam.numericValue = data.sourceNum;

	cpuFullMemory[IC].fullReg = sourceValueParam.fullValueParam;
	IC++;
	
	DesinationSymbolParam.fullSymbolParam = 0;
	DesinationSymbolParam.symParam.encodingType = External;
	DesinationSymbolParam.symParam.addressValue = data.symbolDestination->addresse;

	cpuFullMemory[IC].fullReg = DesinationSymbolParam.fullSymbolParam;
	IC++;
}

/*A function to add to the memory a cmp command with a register as its source parameter and a register as its destination parameter*/
void cmpTwoRegisterCmd(parms data)
{
	commandBitField newCmpCommand;
	registersParam srcDstRegistersParam;

	newCmpCommand.fullCommandInt = 0;
	newCmpCommand.cBitField.encodingType = External;
	newCmpCommand.cBitField.sourceOperandAddressing = DirectRegister;
	newCmpCommand.cBitField.destinationOperandAddressing = DirectRegister;
	newCmpCommand.cBitField.opcode = opcodesArray[1].opcodeNum;

	cpuFullMemory[IC].fullReg = newCmpCommand.fullCommandInt;
	IC++;

	srcDstRegistersParam.fullRegParam = 0;
	srcDstRegistersParam.regParam.encodingType = External;
	srcDstRegistersParam.regParam.regSource = data.eRegSource;
	srcDstRegistersParam.regParam.regDestination = data.eRegDestination;

	cpuFullMemory[IC].fullReg = srcDstRegistersParam.fullRegParam;
	IC++;
}

/*A function to add to the memory a cmp command with a register as its source parameter and a symbol parameter as its destination parameter*/
void cmpRegisterSymbolCmd(parms data)
{
	commandBitField newCmpCommand;
	registersParam sourceRegisterParam;
	symbolParam destinationSymbolParam;

	newCmpCommand.fullCommandInt = 0;
	if(data.symbolDestination->external)
		newCmpCommand.cBitField.encodingType = External;
	else
		newCmpCommand.cBitField.encodingType = Relocatable;
	newCmpCommand.cBitField.sourceOperandAddressing = DirectRegister;
	newCmpCommand.cBitField.destinationOperandAddressing = Direct;
	newCmpCommand.cBitField.opcode = opcodesArray[1].opcodeNum;

	cpuFullMemory[IC].fullReg = newCmpCommand.fullCommandInt;
	IC++;

	sourceRegisterParam.fullRegParam = 0;
	sourceRegisterParam.regParam.encodingType = External;
	sourceRegisterParam.regParam.regSource = data.eRegSource;

	cpuFullMemory[IC].fullReg = sourceRegisterParam.fullRegParam;
	IC++;

	destinationSymbolParam.fullSymbolParam = 0;
	destinationSymbolParam.symParam.encodingType = Relocatable;
	destinationSymbolParam.symParam.addressValue = data.symbolDestination->addresse;

	cpuFullMemory[IC].fullReg = destinationSymbolParam.fullSymbolParam;
	IC++;
}

/*A function to add to the memory a cmp command with a symbol paramater as its source parameter and a register as its destination parameter*/
void cmpSymbolRegisterCmd(parms data)
{
	commandBitField newCmpCommand;
	symbolParam sourceSymbolParam;
	registersParam destinationRegisterParam;

	newCmpCommand.fullCommandInt = 0;
	newCmpCommand.cBitField.encodingType = External;
	newCmpCommand.cBitField.sourceOperandAddressing = Direct;
	newCmpCommand.cBitField.destinationOperandAddressing = DirectRegister;
	newCmpCommand.cBitField.opcode = opcodesArray[1].opcodeNum;

	cpuFullMemory[IC].fullReg = newCmpCommand.fullCommandInt;
	IC++;

	sourceSymbolParam.fullSymbolParam = 0;
	sourceSymbolParam.symParam.encodingType = Relocatable;
	sourceSymbolParam.symParam.addressValue = data.symbolSource->addresse;

	cpuFullMemory[IC].fullReg = sourceSymbolParam.fullSymbolParam;
	IC++;
	
	destinationRegisterParam.fullRegParam = 0;
	destinationRegisterParam.regParam.encodingType = External;
	destinationRegisterParam.regParam.regDestination = data.eRegDestination;

	cpuFullMemory[IC].fullReg = destinationRegisterParam.fullRegParam;
	IC++;
}

/*A function to add to the memory a cmp command with a symbol paramater as its source parameter and a symbol parameter as its destination parameter*/
void cmpSymbolSymbolCmd(parms data)
{
	commandBitField newCmpCommand;
	symbolParam SourceSymbolParam;
	symbolParam DesinationSymbolParam;

	newCmpCommand.fullCommandInt = 0;
	if(data.symbolDestination->external)
		newCmpCommand.cBitField.encodingType = External;
	else
		newCmpCommand.cBitField.encodingType = Relocatable;
	newCmpCommand.cBitField.sourceOperandAddressing = Direct;
	newCmpCommand.cBitField.destinationOperandAddressing = DirectRegister;
	newCmpCommand.cBitField.opcode = opcodesArray[1].opcodeNum;

	cpuFullMemory[IC].fullReg = newCmpCommand.fullCommandInt;
	IC++;

	SourceSymbolParam.fullSymbolParam = 0;
	SourceSymbolParam.symParam.encodingType = Relocatable;
	SourceSymbolParam.symParam.addressValue = data.symbolSource->addresse;

	cpuFullMemory[IC].fullReg = SourceSymbolParam.fullSymbolParam;
	IC++;
	
	DesinationSymbolParam.fullSymbolParam = 0;
	DesinationSymbolParam.symParam.encodingType = External;
	DesinationSymbolParam.symParam.addressValue = data.symbolDestination->addresse;

	cpuFullMemory[IC].fullReg = DesinationSymbolParam.fullSymbolParam;
	IC++;
}

/*A function to add to the memory a cmp command with a numeric value as its source parameter and a register as its destination parameter*/
void cmpValueRegisterCmd(parms data)
{
	commandBitField newCmpCommand;	
	valueParam sourceValueParam;
	registersParam destinationRegistersParam;

	newCmpCommand.fullCommandInt = 0;
	newCmpCommand.cBitField.encodingType = External;
	newCmpCommand.cBitField.sourceOperandAddressing = Immediate;
	newCmpCommand.cBitField.destinationOperandAddressing = DirectRegister;
	newCmpCommand.cBitField.opcode = opcodesArray[1].opcodeNum;

	cpuFullMemory[IC].fullReg = newCmpCommand.fullCommandInt;
	IC++;

	sourceValueParam.fullValueParam = 0;
	sourceValueParam.valParam.encodingType = Absolute;
	sourceValueParam.valParam.numericValue = data.sourceNum;

	cpuFullMemory[IC].fullReg = sourceValueParam.fullValueParam;
	IC++;

	destinationRegistersParam.fullRegParam = 0;
	destinationRegistersParam.regParam.encodingType = External;
	destinationRegistersParam.regParam.regDestination = data.eRegDestination;

	cpuFullMemory[IC].fullReg = destinationRegistersParam.fullRegParam;
	IC++;
}

/*A function to add to the memory a cmp command with a numeric value as its source parameter and a symbol parameter as its destination parameter*/
void cmpValueSymbolCmd(parms data)
{
	commandBitField newCmpCommand;
	valueParam sourceValueParam;
	symbolParam DesinationSymbolParam;

	newCmpCommand.fullCommandInt = 0;
	if(data.symbolDestination->external)
		newCmpCommand.cBitField.encodingType = External;
	else
		newCmpCommand.cBitField.encodingType = Relocatable;
	newCmpCommand.cBitField.sourceOperandAddressing = Direct;
	newCmpCommand.cBitField.destinationOperandAddressing = DirectRegister;
	newCmpCommand.cBitField.opcode = opcodesArray[1].opcodeNum;

	cpuFullMemory[IC].fullReg = newCmpCommand.fullCommandInt;
	IC++;

	sourceValueParam.fullValueParam = 0;
	sourceValueParam.valParam.encodingType = Absolute;
	sourceValueParam.valParam.numericValue = data.sourceNum;

	cpuFullMemory[IC].fullReg = sourceValueParam.fullValueParam;
	IC++;
	
	DesinationSymbolParam.fullSymbolParam = 0;
	DesinationSymbolParam.symParam.encodingType = External;
	DesinationSymbolParam.symParam.addressValue = data.symbolDestination->addresse;

	cpuFullMemory[IC].fullReg = DesinationSymbolParam.fullSymbolParam;
	IC++;
}

/*A function to add to the memory a add command with a register as its source parameter and a register as its destination parameter*/
void addTwoRegisterCmd(parms data)
{
	commandBitField newAddCommand;
	registersParam srcDstRegistersParam;

	newAddCommand.fullCommandInt = 0;
	newAddCommand.cBitField.encodingType = External;
	newAddCommand.cBitField.sourceOperandAddressing = DirectRegister;
	newAddCommand.cBitField.destinationOperandAddressing = DirectRegister;
	newAddCommand.cBitField.opcode = opcodesArray[2].opcodeNum;

	cpuFullMemory[IC].fullReg = newAddCommand.fullCommandInt;
	IC++;

	srcDstRegistersParam.fullRegParam = 0;
	srcDstRegistersParam.regParam.encodingType = External;
	srcDstRegistersParam.regParam.regSource = data.eRegSource;
	srcDstRegistersParam.regParam.regDestination = data.eRegDestination;

	cpuFullMemory[IC].fullReg = srcDstRegistersParam.fullRegParam;
	IC++;
}

/*A function to add to the memory a add command with a register as its source parameter and a symbol parameter as its destination parameter*/
void addRegisterSymbolCmd(parms data)
{
	commandBitField newAddCommand;
	registersParam sourceRegisterParam;
	symbolParam destinationSymbolParam;

	newAddCommand.fullCommandInt = 0;
	if(data.symbolDestination->external)
		newAddCommand.cBitField.encodingType = External;
	else
		newAddCommand.cBitField.encodingType = Relocatable;
	newAddCommand.cBitField.sourceOperandAddressing = DirectRegister;
	newAddCommand.cBitField.destinationOperandAddressing = Direct;
	newAddCommand.cBitField.opcode = opcodesArray[1].opcodeNum;

	cpuFullMemory[IC].fullReg = newAddCommand.fullCommandInt;
	IC++;

	sourceRegisterParam.fullRegParam = 0;
	sourceRegisterParam.regParam.encodingType = External;
	sourceRegisterParam.regParam.regSource = data.eRegSource;

	cpuFullMemory[IC].fullReg = sourceRegisterParam.fullRegParam;
	IC++;

	destinationSymbolParam.fullSymbolParam = 0;
	destinationSymbolParam.symParam.encodingType = Relocatable;
	destinationSymbolParam.symParam.addressValue = data.symbolDestination->addresse;

	cpuFullMemory[IC].fullReg = destinationSymbolParam.fullSymbolParam;
	IC++;
}

/*A function to add to the memory a add command with a symbol paramater as its source parameter and a register as its destination parameter*/
void addSymbolRegisterCmd(parms data)
{
	commandBitField newAddCommand;
	symbolParam sourceSymbolParam;
	registersParam destinationRegisterParam;

	newAddCommand.fullCommandInt = 0;
	newAddCommand.cBitField.encodingType = External;
	newAddCommand.cBitField.sourceOperandAddressing = Direct;
	newAddCommand.cBitField.destinationOperandAddressing = DirectRegister;
	newAddCommand.cBitField.opcode = opcodesArray[0].opcodeNum;

	cpuFullMemory[IC].fullReg = newAddCommand.fullCommandInt;
	IC++;

	sourceSymbolParam.fullSymbolParam = 0;
	sourceSymbolParam.symParam.encodingType = Relocatable;
	sourceSymbolParam.symParam.addressValue = data.symbolSource->addresse;

	cpuFullMemory[IC].fullReg = sourceSymbolParam.fullSymbolParam;
	IC++;
	
	destinationRegisterParam.fullRegParam = 0;
	destinationRegisterParam.regParam.encodingType = External;
	destinationRegisterParam.regParam.regDestination = data.eRegDestination;

	cpuFullMemory[IC].fullReg = destinationRegisterParam.fullRegParam;
	IC++;
}

/*A function to add to the memory a add command with a symbol paramater as its source parameter and a symbol parameter as its destination parameter*/
void addSymbolSymbolCmd(parms data)
{
	commandBitField newAddCommand;
	symbolParam SourceSymbolParam;
	symbolParam DesinationSymbolParam;

	newAddCommand.fullCommandInt = 0;
	if(data.symbolDestination->external)
		newAddCommand.cBitField.encodingType = External;
	else
		newAddCommand.cBitField.encodingType = Relocatable;
	newAddCommand.cBitField.sourceOperandAddressing = Direct;
	newAddCommand.cBitField.destinationOperandAddressing = DirectRegister;
	newAddCommand.cBitField.opcode = opcodesArray[1].opcodeNum;

	cpuFullMemory[IC].fullReg = newAddCommand.fullCommandInt;
	IC++;

	SourceSymbolParam.fullSymbolParam = 0;
	SourceSymbolParam.symParam.encodingType = Relocatable;
	SourceSymbolParam.symParam.addressValue = data.symbolSource->addresse;

	cpuFullMemory[IC].fullReg = SourceSymbolParam.fullSymbolParam;
	IC++;
	
	DesinationSymbolParam.fullSymbolParam = 0;
	DesinationSymbolParam.symParam.encodingType = External;
	DesinationSymbolParam.symParam.addressValue = data.symbolDestination->addresse;

	cpuFullMemory[IC].fullReg = DesinationSymbolParam.fullSymbolParam;
	IC++;
}

/*A function to add to the memory a add command with a numeric value as its source parameter and a register as its destination parameter*/
void addValueRegisterCmd(parms data)
{
	commandBitField newAddCommand;
	valueParam sourceValueParam;
	registersParam destinationRegistersParam;

	newAddCommand.fullCommandInt = 0;
	newAddCommand.cBitField.encodingType = External;
	newAddCommand.cBitField.sourceOperandAddressing = Immediate;
	newAddCommand.cBitField.destinationOperandAddressing = DirectRegister;
	newAddCommand.cBitField.opcode = opcodesArray[2].opcodeNum;

	cpuFullMemory[IC].fullReg = newAddCommand.fullCommandInt;
	IC++;

	sourceValueParam.fullValueParam = 0;
	sourceValueParam.valParam.encodingType = Absolute;
	sourceValueParam.valParam.numericValue = data.sourceNum;

	cpuFullMemory[IC].fullReg = sourceValueParam.fullValueParam;
	IC++;

	destinationRegistersParam.fullRegParam = 0;
	destinationRegistersParam.regParam.encodingType = External;
	destinationRegistersParam.regParam.regDestination = data.eRegDestination;

	cpuFullMemory[IC].fullReg = destinationRegistersParam.fullRegParam;
	IC++;
}

/*A function to add to the memory a add command with a numeric value as its source parameter and a symbol parameter as its destination parameter*/
void addValueSymbolCmd(parms data)
{
	commandBitField newAddCommand;
	valueParam sourceValueParam;
	symbolParam DesinationSymbolParam;

	newAddCommand.fullCommandInt = 0;
	if(data.symbolDestination->external)
		newAddCommand.cBitField.encodingType = External;
	else
		newAddCommand.cBitField.encodingType = Relocatable;
	newAddCommand.cBitField.sourceOperandAddressing = Direct;
	newAddCommand.cBitField.destinationOperandAddressing = DirectRegister;
	newAddCommand.cBitField.opcode = opcodesArray[1].opcodeNum;

	cpuFullMemory[IC].fullReg = newAddCommand.fullCommandInt;
	IC++;

	sourceValueParam.fullValueParam = 0;
	sourceValueParam.valParam.encodingType = Absolute;
	sourceValueParam.valParam.numericValue = data.sourceNum;

	cpuFullMemory[IC].fullReg = sourceValueParam.fullValueParam;
	IC++;
	
	DesinationSymbolParam.fullSymbolParam = 0;
	DesinationSymbolParam.symParam.encodingType = External;
	DesinationSymbolParam.symParam.addressValue = data.symbolDestination->addresse;

	cpuFullMemory[IC].fullReg = DesinationSymbolParam.fullSymbolParam;
	IC++;
}

/*A function to add to the memory a sub command with a register as its source parameter and a register as its destination parameter*/
void subTwoRegisterCmd(parms data)
{
	commandBitField newSubCommand;
	registersParam srcDstRegistersParam;

	newSubCommand.fullCommandInt = 0;
	newSubCommand.cBitField.encodingType = External;
	newSubCommand.cBitField.sourceOperandAddressing = DirectRegister;
	newSubCommand.cBitField.destinationOperandAddressing = DirectRegister;
	newSubCommand.cBitField.opcode = opcodesArray[3].opcodeNum;

	cpuFullMemory[IC].fullReg = newSubCommand.fullCommandInt;
	IC++;

	srcDstRegistersParam.fullRegParam = 0;
	srcDstRegistersParam.regParam.encodingType = External;
	srcDstRegistersParam.regParam.regSource = data.eRegSource;
	srcDstRegistersParam.regParam.regDestination = data.eRegDestination;

	cpuFullMemory[IC].fullReg = srcDstRegistersParam.fullRegParam;
	IC++;
}

/*A function to add to the memory a sub command with a register as its source parameter and a symbol parameter as its destination parameter*/
void subRegisterSymbolCmd(parms data)
{
	commandBitField newSubCommand;
	registersParam sourceRegisterParam;
	symbolParam destinationSymbolParam;

	newSubCommand.fullCommandInt = 0;
	if(data.symbolDestination->external)
		newSubCommand.cBitField.encodingType = External;
	else
		newSubCommand.cBitField.encodingType = Relocatable;
	newSubCommand.cBitField.sourceOperandAddressing = DirectRegister;
	newSubCommand.cBitField.destinationOperandAddressing = Direct;
	newSubCommand.cBitField.opcode = opcodesArray[0].opcodeNum;

	cpuFullMemory[IC].fullReg = newSubCommand.fullCommandInt;
	IC++;

	sourceRegisterParam.fullRegParam = 0;
	sourceRegisterParam.regParam.encodingType = External;
	sourceRegisterParam.regParam.regSource = data.eRegSource;

	cpuFullMemory[IC].fullReg = sourceRegisterParam.fullRegParam;
	IC++;

	destinationSymbolParam.fullSymbolParam = 0;
	destinationSymbolParam.symParam.encodingType = Relocatable;
	destinationSymbolParam.symParam.addressValue = data.symbolDestination->addresse;

	cpuFullMemory[IC].fullReg = destinationSymbolParam.fullSymbolParam;
	IC++;
}

/*A function to add to the memory a sub command with a symbol paramater as its source parameter and a register as its destination parameter*/
void subSymbolRegisterCmd(parms data)
{
	commandBitField newSubCommand;
	symbolParam sourceSymbolParam;
	registersParam destinationRegisterParam;

	newSubCommand.fullCommandInt = 0;
	newSubCommand.cBitField.encodingType = External;
	newSubCommand.cBitField.sourceOperandAddressing = Direct;
	newSubCommand.cBitField.destinationOperandAddressing = DirectRegister;
	newSubCommand.cBitField.opcode = opcodesArray[0].opcodeNum;

	cpuFullMemory[IC].fullReg = newSubCommand.fullCommandInt;
	IC++;

	sourceSymbolParam.fullSymbolParam = 0;
	sourceSymbolParam.symParam.encodingType = Relocatable;
	sourceSymbolParam.symParam.addressValue = data.symbolSource->addresse;

	cpuFullMemory[IC].fullReg = sourceSymbolParam.fullSymbolParam;
	IC++;
	
	destinationRegisterParam.fullRegParam = 0;
	destinationRegisterParam.regParam.encodingType = External;
	destinationRegisterParam.regParam.regDestination = data.eRegDestination;

	cpuFullMemory[IC].fullReg = destinationRegisterParam.fullRegParam;
	IC++;
}

/*A function to add to the memory a sub command with a symbol paramater as its source parameter and a symbol parameter as its destination parameter*/
void subSymbolSymbolCmd(parms data)
{
	commandBitField newSubCommand;
	symbolParam SourceSymbolParam;
	symbolParam DesinationSymbolParam;

	newSubCommand.fullCommandInt = 0;
	if(data.symbolDestination->external)
		newSubCommand.cBitField.encodingType = External;
	else
		newSubCommand.cBitField.encodingType = Relocatable;
	newSubCommand.cBitField.sourceOperandAddressing = Direct;
	newSubCommand.cBitField.destinationOperandAddressing = DirectRegister;
	newSubCommand.cBitField.opcode = opcodesArray[1].opcodeNum;

	cpuFullMemory[IC].fullReg = newSubCommand.fullCommandInt;
	IC++;

	SourceSymbolParam.fullSymbolParam = 0;
	SourceSymbolParam.symParam.encodingType = Relocatable;
	SourceSymbolParam.symParam.addressValue = data.symbolSource->addresse;

	cpuFullMemory[IC].fullReg = SourceSymbolParam.fullSymbolParam;
	IC++;
	
	DesinationSymbolParam.fullSymbolParam = 0;
	DesinationSymbolParam.symParam.encodingType = External;
	DesinationSymbolParam.symParam.addressValue = data.symbolDestination->addresse;

	cpuFullMemory[IC].fullReg = DesinationSymbolParam.fullSymbolParam;
	IC++;
}

/*A function to add to the memory a sub command with a numeric value as its source parameter and a register as its destination parameter*/
void subValueRegisterCmd(parms data)
{
	commandBitField newSubCommand;
	valueParam sourceValueParam;
	registersParam destinationRegistersParam;
	

	newSubCommand.fullCommandInt = 0;
	newSubCommand.cBitField.encodingType = External;
	newSubCommand.cBitField.sourceOperandAddressing = Immediate;
	newSubCommand.cBitField.destinationOperandAddressing = DirectRegister;
	newSubCommand.cBitField.opcode = opcodesArray[3].opcodeNum;

	cpuFullMemory[IC].fullReg = newSubCommand.fullCommandInt;
	IC++;

	sourceValueParam.fullValueParam = 0;
	sourceValueParam.valParam.encodingType = Absolute;
	sourceValueParam.valParam.numericValue = data.sourceNum;

	cpuFullMemory[IC].fullReg = sourceValueParam.fullValueParam;
	IC++;

	destinationRegistersParam.fullRegParam = 0;
	destinationRegistersParam.regParam.encodingType = External;
	destinationRegistersParam.regParam.regDestination = data.eRegDestination;

	cpuFullMemory[IC].fullReg = destinationRegistersParam.fullRegParam;
	IC++;
}

/*A function to add to the memory a sub command with a numeric value as its source parameter and a symbol parameter as its destination parameter*/
void subValueSymbolCmd(parms data)
{
	commandBitField newSubCommand;
	valueParam sourceValueParam;
	symbolParam DesinationSymbolParam;

	newSubCommand.fullCommandInt = 0;
	if(data.symbolDestination->external)
		newSubCommand.cBitField.encodingType = External;
	else
		newSubCommand.cBitField.encodingType = Relocatable;
	newSubCommand.cBitField.sourceOperandAddressing = Direct;
	newSubCommand.cBitField.destinationOperandAddressing = DirectRegister;
	newSubCommand.cBitField.opcode = opcodesArray[1].opcodeNum;

	cpuFullMemory[IC].fullReg = newSubCommand.fullCommandInt;
	IC++;

	sourceValueParam.fullValueParam = 0;
	sourceValueParam.valParam.encodingType = Absolute;
	sourceValueParam.valParam.numericValue = data.sourceNum;

	cpuFullMemory[IC].fullReg = sourceValueParam.fullValueParam;
	IC++;
	
	DesinationSymbolParam.fullSymbolParam = 0;
	DesinationSymbolParam.symParam.encodingType = External;
	DesinationSymbolParam.symParam.addressValue = data.symbolDestination->addresse;

	cpuFullMemory[IC].fullReg = DesinationSymbolParam.fullSymbolParam;
	IC++;
}

/*A function to add to the memory a lea command with a register as its source parameter and a register as its destination parameter*/
void leaTwoRegisterCmd(parms data)
{
	commandBitField newLeaCommand;
	registersParam srcDstRegistersParam;

	newLeaCommand.fullCommandInt = 0;
	newLeaCommand.cBitField.encodingType = External;
	newLeaCommand.cBitField.sourceOperandAddressing = DirectRegister;
	newLeaCommand.cBitField.destinationOperandAddressing = DirectRegister;
	newLeaCommand.cBitField.opcode = opcodesArray[6].opcodeNum;

	cpuFullMemory[IC].fullReg = newLeaCommand.fullCommandInt;
	IC++;

	srcDstRegistersParam.fullRegParam = 0;
	srcDstRegistersParam.regParam.encodingType = External;
	srcDstRegistersParam.regParam.regSource = data.eRegSource;
	srcDstRegistersParam.regParam.regDestination = data.eRegDestination;

	cpuFullMemory[IC].fullReg = srcDstRegistersParam.fullRegParam;
	IC++;
}

/*A function to add to the memory a lea command with a register as its source parameter and a symbol parameter as its destination parameter*/
void leaRegisterSymbolCmd(parms data)
{
	commandBitField newLeaCommand;
	registersParam sourceRegisterParam;
	symbolParam destinationSymbolParam;

	newLeaCommand.fullCommandInt = 0;
	if(data.symbolDestination->external)
		newLeaCommand.cBitField.encodingType = External;
	else
		newLeaCommand.cBitField.encodingType = Relocatable;
	newLeaCommand.cBitField.sourceOperandAddressing = DirectRegister;
	newLeaCommand.cBitField.destinationOperandAddressing = Direct;
	newLeaCommand.cBitField.opcode = opcodesArray[0].opcodeNum;

	cpuFullMemory[IC].fullReg = newLeaCommand.fullCommandInt;
	IC++;

	sourceRegisterParam.fullRegParam = 0;
	sourceRegisterParam.regParam.encodingType = External;
	sourceRegisterParam.regParam.regSource = data.eRegSource;

	cpuFullMemory[IC].fullReg = sourceRegisterParam.fullRegParam;
	IC++;

	destinationSymbolParam.fullSymbolParam = 0;
	destinationSymbolParam.symParam.encodingType = Relocatable;
	destinationSymbolParam.symParam.addressValue = data.symbolDestination->addresse;

	cpuFullMemory[IC].fullReg = destinationSymbolParam.fullSymbolParam;
	IC++;
}

/*A function to add to the memory a lea command with a symbol paramater as its source parameter and a register as its destination parameter*/
void leaSymbolRegisterCmd(parms data)
{
	commandBitField newLeaCommand;
	symbolParam sourceSymbolParam;
	registersParam destinationRegisterParam;

	newLeaCommand.fullCommandInt = 0;
	newLeaCommand.cBitField.encodingType = External;
	newLeaCommand.cBitField.sourceOperandAddressing = Direct;
	newLeaCommand.cBitField.destinationOperandAddressing = DirectRegister;
	newLeaCommand.cBitField.opcode = opcodesArray[0].opcodeNum;

	cpuFullMemory[IC].fullReg = newLeaCommand.fullCommandInt;
	IC++;

	sourceSymbolParam.fullSymbolParam = 0;
	sourceSymbolParam.symParam.encodingType = Relocatable;
	sourceSymbolParam.symParam.addressValue = data.symbolSource->addresse;

	cpuFullMemory[IC].fullReg = sourceSymbolParam.fullSymbolParam;
	IC++;
	
	destinationRegisterParam.fullRegParam = 0;
	destinationRegisterParam.regParam.encodingType = External;
	destinationRegisterParam.regParam.regDestination = data.eRegDestination;

	cpuFullMemory[IC].fullReg = destinationRegisterParam.fullRegParam;
	IC++;
}

/*A function to add to the memory a lea command with a symbol paramater as its source parameter and a symbol parameter as its destination parameter*/
void leaSymbolSymbolCmd(parms data)
{
	commandBitField newLeaCommand;
	symbolParam SourceSymbolParam;
	symbolParam DesinationSymbolParam;

	newLeaCommand.fullCommandInt = 0;
	if(data.symbolDestination->external)
		newLeaCommand.cBitField.encodingType = External;
	else
		newLeaCommand.cBitField.encodingType = Relocatable;
	newLeaCommand.cBitField.sourceOperandAddressing = Direct;
	newLeaCommand.cBitField.destinationOperandAddressing = DirectRegister;
	newLeaCommand.cBitField.opcode = opcodesArray[1].opcodeNum;

	cpuFullMemory[IC].fullReg = newLeaCommand.fullCommandInt;
	IC++;

	SourceSymbolParam.fullSymbolParam = 0;
	SourceSymbolParam.symParam.encodingType = Relocatable;
	SourceSymbolParam.symParam.addressValue = data.symbolSource->addresse;

	cpuFullMemory[IC].fullReg = SourceSymbolParam.fullSymbolParam;
	IC++;
	
	DesinationSymbolParam.fullSymbolParam = 0;
	DesinationSymbolParam.symParam.encodingType = External;
	DesinationSymbolParam.symParam.addressValue = data.symbolDestination->addresse;

	cpuFullMemory[IC].fullReg = DesinationSymbolParam.fullSymbolParam;
	IC++;
}

/*A function to add to the memory a lea command with a numeric value as its source parameter and a register as its destination parameter*/
void leaValueRegisterCmd(parms data)
{
	commandBitField newLeaCommand;
	valueParam sourceValueParam;
	registersParam destinationRegistersParam;

	newLeaCommand.fullCommandInt = 0;
	newLeaCommand.cBitField.encodingType = External;
	newLeaCommand.cBitField.sourceOperandAddressing = Immediate;
	newLeaCommand.cBitField.destinationOperandAddressing = DirectRegister;
	newLeaCommand.cBitField.opcode = opcodesArray[6].opcodeNum;

	cpuFullMemory[IC].fullReg = newLeaCommand.fullCommandInt;
	IC++;

	sourceValueParam.fullValueParam = 0;
	sourceValueParam.valParam.encodingType = Absolute;
	sourceValueParam.valParam.numericValue = data.sourceNum;

	cpuFullMemory[IC].fullReg = sourceValueParam.fullValueParam;
	IC++;

	destinationRegistersParam.fullRegParam = 0;
	destinationRegistersParam.regParam.encodingType = External;
	destinationRegistersParam.regParam.regDestination = data.eRegDestination;

	cpuFullMemory[IC].fullReg = destinationRegistersParam.fullRegParam;
	IC++;
}

/*A function to add to the memory a lea command with a numeric value as its source parameter and a symbol parameter as its destination parameter*/
void leaValueSymbolCmd(parms data)
{
	commandBitField newLeaCommand;
	valueParam sourceValueParam;
	symbolParam DesinationSymbolParam;

	newLeaCommand.fullCommandInt = 0;
	if(data.symbolDestination->external)
		newLeaCommand.cBitField.encodingType = External;
	else
		newLeaCommand.cBitField.encodingType = Relocatable;
	newLeaCommand.cBitField.sourceOperandAddressing = Direct;
	newLeaCommand.cBitField.destinationOperandAddressing = DirectRegister;
	newLeaCommand.cBitField.opcode = opcodesArray[1].opcodeNum;

	cpuFullMemory[IC].fullReg = newLeaCommand.fullCommandInt;
	IC++;

	sourceValueParam.fullValueParam = 0;
	sourceValueParam.valParam.encodingType = Absolute;
	sourceValueParam.valParam.numericValue = data.sourceNum;

	cpuFullMemory[IC].fullReg = sourceValueParam.fullValueParam;
	IC++;
	
	DesinationSymbolParam.fullSymbolParam = 0;
	DesinationSymbolParam.symParam.encodingType = External;
	DesinationSymbolParam.symParam.addressValue = data.symbolDestination->addresse;

	cpuFullMemory[IC].fullReg = DesinationSymbolParam.fullSymbolParam;
	IC++;
}

/*A function to add to the memory a not command with a register as its destination parameter*/
void notRegisterCmd(parms data)
{
	commandBitField newNotCommand;
	registersParam destinationRegistersParam;

	newNotCommand.fullCommandInt = 0;
	newNotCommand.cBitField.encodingType = External;
	newNotCommand.cBitField.destinationOperandAddressing = DirectRegister;
	newNotCommand.cBitField.opcode = opcodesArray[4].opcodeNum;

	cpuFullMemory[IC].fullReg = newNotCommand.fullCommandInt;
	IC++;

	destinationRegistersParam.fullRegParam = 0;
	destinationRegistersParam.regParam.encodingType = External;
	destinationRegistersParam.regParam.regDestination = data.eRegDestination;

	cpuFullMemory[IC].fullReg = destinationRegistersParam.fullRegParam;
	IC++;
}

/*A function to add to the memory a not command with a symbol paramater as its destination parameter*/
void notSymbolCmd(parms data)
{
	commandBitField newNotCommand;
	symbolParam DesinationSymbolParam;

	newNotCommand.fullCommandInt = 0;
	if(data.symbolDestination->external)
		newNotCommand.cBitField.encodingType = External;
	else
		newNotCommand.cBitField.encodingType = Relocatable;
	newNotCommand.cBitField.destinationOperandAddressing = Direct;
	newNotCommand.cBitField.opcode = opcodesArray[4].opcodeNum;

	cpuFullMemory[IC].fullReg = newNotCommand.fullCommandInt;
	IC++;

	DesinationSymbolParam.fullSymbolParam = 0;
	DesinationSymbolParam.symParam.encodingType = External;
	DesinationSymbolParam.symParam.addressValue = data.symbolDestination->addresse;

	cpuFullMemory[IC].fullReg = DesinationSymbolParam.fullSymbolParam;
	IC++;
}

/*A function to add to the memory a clr command with a register as its destination parameter*/
void clrRegisterCmd(parms data)
{
	commandBitField newClrCommand;
	registersParam destinationRegistersParam;

	newClrCommand.fullCommandInt = 0;
	newClrCommand.cBitField.encodingType = External;
	newClrCommand.cBitField.destinationOperandAddressing = DirectRegister;
	newClrCommand.cBitField.opcode = opcodesArray[5].opcodeNum;

	cpuFullMemory[IC].fullReg = newClrCommand.fullCommandInt;
	IC++;

	destinationRegistersParam.fullRegParam = 0;
	destinationRegistersParam.regParam.encodingType = External;
	destinationRegistersParam.regParam.regDestination = data.eRegDestination;

	cpuFullMemory[IC].fullReg = destinationRegistersParam.fullRegParam;
	IC++;
}

/*A function to add to the memory a clr command with a symbol paramater as its destination parameter*/
void clrSymbolCmd(parms data)
{
	commandBitField newClrCommand;
	symbolParam DesinationSymbolParam;

	newClrCommand.fullCommandInt = 0;
	if(data.symbolDestination->external)
		newClrCommand.cBitField.encodingType = External;
	else
		newClrCommand.cBitField.encodingType = Relocatable;
	newClrCommand.cBitField.destinationOperandAddressing = Direct;
	newClrCommand.cBitField.opcode = opcodesArray[5].opcodeNum;

	cpuFullMemory[IC].fullReg = newClrCommand.fullCommandInt;
	IC++;

	DesinationSymbolParam.fullSymbolParam = 0;
	DesinationSymbolParam.symParam.encodingType = External;
	DesinationSymbolParam.symParam.addressValue = data.symbolDestination->addresse;

	cpuFullMemory[IC].fullReg = DesinationSymbolParam.fullSymbolParam;
	IC++;
}

/*A function to add to the memory an inc command with a register as its destination parameter*/
void incRegisterCmd(parms data)
{
	commandBitField newIncCommand;
	registersParam destinationRegistersParam;

	newIncCommand.fullCommandInt = 0;
	newIncCommand.cBitField.encodingType = External;
	newIncCommand.cBitField.destinationOperandAddressing = DirectRegister;
	newIncCommand.cBitField.opcode = opcodesArray[7].opcodeNum;

	cpuFullMemory[IC].fullReg = newIncCommand.fullCommandInt;
	IC++;

	destinationRegistersParam.fullRegParam = 0;
	destinationRegistersParam.regParam.encodingType = External;
	destinationRegistersParam.regParam.regDestination = data.eRegDestination;

	cpuFullMemory[IC].fullReg = destinationRegistersParam.fullRegParam;
	IC++;
}

/*A function to add to the memory a inc command with a symbol paramater as its destination parameter*/
void incSymbolCmd(parms data)
{
	commandBitField newIncCommand;
	symbolParam DesinationSymbolParam;

	newIncCommand.fullCommandInt = 0;
	if(data.symbolDestination->external)
		newIncCommand.cBitField.encodingType = External;
	else
		newIncCommand.cBitField.encodingType = Relocatable;
	newIncCommand.cBitField.destinationOperandAddressing = Direct;
	newIncCommand.cBitField.opcode = opcodesArray[7].opcodeNum;

	cpuFullMemory[IC].fullReg = newIncCommand.fullCommandInt;
	IC++;

	DesinationSymbolParam.fullSymbolParam = 0;
	DesinationSymbolParam.symParam.encodingType = External;
	DesinationSymbolParam.symParam.addressValue = data.symbolDestination->addresse;

	cpuFullMemory[IC].fullReg = DesinationSymbolParam.fullSymbolParam;
	IC++;
}

/*A function to add to the memory a dec command with a register as its destination parameter*/
void decRegisterCmd(parms data)
{
	commandBitField newDecCommand;
	registersParam destinationRegistersParam;

	newDecCommand.fullCommandInt = 0;
	newDecCommand.cBitField.encodingType = External;
	newDecCommand.cBitField.destinationOperandAddressing = DirectRegister;
	newDecCommand.cBitField.opcode = opcodesArray[8].opcodeNum;

	cpuFullMemory[IC].fullReg = newDecCommand.fullCommandInt;
	IC++;

	destinationRegistersParam.fullRegParam = 0;
	destinationRegistersParam.regParam.encodingType = External;
	destinationRegistersParam.regParam.regDestination = data.eRegDestination;

	cpuFullMemory[IC].fullReg = destinationRegistersParam.fullRegParam;
	IC++;
}

/*A function to add to the memory a dec command with a symbol paramater as its destination parameter*/
void decSymbolCmd(parms data)
{
	commandBitField newDecCommand;
	symbolParam DesinationSymbolParam;

	newDecCommand.fullCommandInt = 0;
	if(data.symbolDestination->external)
		newDecCommand.cBitField.encodingType = External;
	else
		newDecCommand.cBitField.encodingType = Relocatable;
	newDecCommand.cBitField.destinationOperandAddressing = Direct;
	newDecCommand.cBitField.opcode = opcodesArray[7].opcodeNum;

	cpuFullMemory[IC].fullReg = newDecCommand.fullCommandInt;
	IC++;

	DesinationSymbolParam.fullSymbolParam = 0;
	DesinationSymbolParam.symParam.encodingType = External;
	DesinationSymbolParam.symParam.addressValue = data.symbolDestination->addresse;

	cpuFullMemory[IC].fullReg = DesinationSymbolParam.fullSymbolParam;
	IC++;
}

/*A function to add to the memory a jmp command with a register as its destination parameter*/
void jmpRegisterCmd(parms data)
{
	commandBitField newJmpCommand;
	registersParam destinationRegistersParam;

	newJmpCommand.fullCommandInt = 0;
	newJmpCommand.cBitField.encodingType = External;
	newJmpCommand.cBitField.destinationOperandAddressing = DirectRegister;
	newJmpCommand.cBitField.opcode = opcodesArray[9].opcodeNum;

	cpuFullMemory[IC].fullReg = newJmpCommand.fullCommandInt;
	IC++;

	destinationRegistersParam.fullRegParam = 0;
	destinationRegistersParam.regParam.encodingType = External;
	destinationRegistersParam.regParam.regDestination = data.eRegDestination;

	cpuFullMemory[IC].fullReg = destinationRegistersParam.fullRegParam;
	IC++;
}

/*A function to add to the memory a jmp command with a symbol paramater as its destination parameter*/
void jmpSymbolCmd(parms data)
{
	commandBitField newJmpCommand;
	symbolParam DesinationSymbolParam;

	newJmpCommand.fullCommandInt = 0;
	if(data.symbolDestination->external)
		newJmpCommand.cBitField.encodingType = External;
	else
		newJmpCommand.cBitField.encodingType = Relocatable;
	newJmpCommand.cBitField.destinationOperandAddressing = Direct;
	newJmpCommand.cBitField.opcode = opcodesArray[7].opcodeNum;

	cpuFullMemory[IC].fullReg = newJmpCommand.fullCommandInt;
	IC++;

	DesinationSymbolParam.fullSymbolParam = 0;
	DesinationSymbolParam.symParam.encodingType = External;
	DesinationSymbolParam.symParam.addressValue = data.symbolDestination->addresse;

	cpuFullMemory[IC].fullReg = DesinationSymbolParam.fullSymbolParam;
	IC++;
}

/*A function to add to the memory a bne command with a register as its destination parameter*/
void bneRegisterCmd(parms data)
{
	commandBitField newBneCommand;
	registersParam destinationRegistersParam;

	newBneCommand.fullCommandInt = 0;
	newBneCommand.cBitField.encodingType = External;
	newBneCommand.cBitField.destinationOperandAddressing = DirectRegister;
	newBneCommand.cBitField.opcode = opcodesArray[10].opcodeNum;

	cpuFullMemory[IC].fullReg = newBneCommand.fullCommandInt;
	IC++;

	destinationRegistersParam.fullRegParam = 0;
	destinationRegistersParam.regParam.encodingType = External;
	destinationRegistersParam.regParam.regDestination = data.eRegDestination;

	cpuFullMemory[IC].fullReg = destinationRegistersParam.fullRegParam;
	IC++;
}

/*A function to add to the memory a bne command with a symbol paramater as its destination parameter*/
void bneSymbolCmd(parms data)
{
	commandBitField newBneCommand;
	symbolParam DesinationSymbolParam;

	newBneCommand.fullCommandInt = 0;
	if(data.symbolDestination->external)
		newBneCommand.cBitField.encodingType = External;
	else
		newBneCommand.cBitField.encodingType = Relocatable;
	newBneCommand.cBitField.destinationOperandAddressing = Direct;
	newBneCommand.cBitField.opcode = opcodesArray[7].opcodeNum;

	cpuFullMemory[IC].fullReg = newBneCommand.fullCommandInt;
	IC++;

	DesinationSymbolParam.fullSymbolParam = 0;
	DesinationSymbolParam.symParam.encodingType = External;
	DesinationSymbolParam.symParam.addressValue = data.symbolDestination->addresse;

	cpuFullMemory[IC].fullReg = DesinationSymbolParam.fullSymbolParam;
	IC++;
}

/*A function to add to the memory a red command with a register as its destination parameter*/
void redRegisterCmd(parms data)
{
	commandBitField newRedCommand;
	registersParam destinationRegistersParam;

	newRedCommand.fullCommandInt = 0;
	newRedCommand.cBitField.encodingType = External;
	newRedCommand.cBitField.destinationOperandAddressing = DirectRegister;
	newRedCommand.cBitField.opcode = opcodesArray[11].opcodeNum;

	cpuFullMemory[IC].fullReg = newRedCommand.fullCommandInt;
	IC++;

	destinationRegistersParam.fullRegParam = 0;
	destinationRegistersParam.regParam.encodingType = External;
	destinationRegistersParam.regParam.regDestination = data.eRegDestination;

	cpuFullMemory[IC].fullReg = destinationRegistersParam.fullRegParam;
	IC++;
}

/*A function to add to the memory a red command with a symbol paramater as its destination parameter*/
void redSymbolCmd(parms data)
{
	commandBitField newRedCommand;
	symbolParam DesinationSymbolParam;

	newRedCommand.fullCommandInt = 0;
	if(data.symbolDestination->external)
		newRedCommand.cBitField.encodingType = External;
	else
		newRedCommand.cBitField.encodingType = Relocatable;
	newRedCommand.cBitField.destinationOperandAddressing = Direct;
	newRedCommand.cBitField.opcode = opcodesArray[7].opcodeNum;

	cpuFullMemory[IC].fullReg = newRedCommand.fullCommandInt;
	IC++;

	DesinationSymbolParam.fullSymbolParam = 0;
	DesinationSymbolParam.symParam.encodingType = External;
	DesinationSymbolParam.symParam.addressValue = data.symbolDestination->addresse;

	cpuFullMemory[IC].fullReg = DesinationSymbolParam.fullSymbolParam;
	IC++;
}

/*A function to add to the memory a prn command with a register as its destination parameter*/
void prnRegisterCmd(parms data)
{
	commandBitField newPrnCommand;
	registersParam destinationRegistersParam;

	newPrnCommand.fullCommandInt = 0;
	newPrnCommand.cBitField.encodingType = External;
	newPrnCommand.cBitField.destinationOperandAddressing = DirectRegister;
	newPrnCommand.cBitField.opcode = opcodesArray[12].opcodeNum;

	cpuFullMemory[IC].fullReg = newPrnCommand.fullCommandInt;
	IC++;

	destinationRegistersParam.fullRegParam = 0;
	destinationRegistersParam.regParam.encodingType = External;
	destinationRegistersParam.regParam.regDestination = data.eRegDestination;

	cpuFullMemory[IC].fullReg = destinationRegistersParam.fullRegParam;
	IC++;
}

/*A function to add to the memory a prn command with a symbol paramater as its destination parameter*/
void prnSymbolCmd(parms data)
{
	commandBitField newPrnCommand;
	symbolParam DesinationSymbolParam;

	newPrnCommand.fullCommandInt = 0;
	if(data.symbolDestination->external)
		newPrnCommand.cBitField.encodingType = External;
	else
		newPrnCommand.cBitField.encodingType = Relocatable;
	newPrnCommand.cBitField.destinationOperandAddressing = Direct;
	newPrnCommand.cBitField.opcode = opcodesArray[7].opcodeNum;

	cpuFullMemory[IC].fullReg = newPrnCommand.fullCommandInt;
	IC++;

	DesinationSymbolParam.fullSymbolParam = 0;
	DesinationSymbolParam.symParam.encodingType = External;
	DesinationSymbolParam.symParam.addressValue = data.symbolDestination->addresse;

	cpuFullMemory[IC].fullReg = DesinationSymbolParam.fullSymbolParam;
	IC++;
}

/*A function to add to the memory a jsr command with a register as its destination parameter*/
void jsrRegisterCmd(parms data)
{
	commandBitField newJsrCommand;
	registersParam destinationRegistersParam;

	newJsrCommand.fullCommandInt = 0;
	newJsrCommand.cBitField.encodingType = External;
	newJsrCommand.cBitField.destinationOperandAddressing = DirectRegister;
	newJsrCommand.cBitField.opcode = opcodesArray[13].opcodeNum;

	cpuFullMemory[IC].fullReg = newJsrCommand.fullCommandInt;
	IC++;

	destinationRegistersParam.fullRegParam = 0;
	destinationRegistersParam.regParam.encodingType = External;
	destinationRegistersParam.regParam.regDestination = data.eRegDestination;

	cpuFullMemory[IC].fullReg = destinationRegistersParam.fullRegParam;
	IC++;
}

/*A function to add to the memory a jsr command with a symbol paramater as its destination parameter*/
void jsrSymbolCmd(parms data)
{
	commandBitField newJsrCommand;
	symbolParam DesinationSymbolParam;

	newJsrCommand.fullCommandInt = 0;
	if(data.symbolDestination->external)
		newJsrCommand.cBitField.encodingType = External;
	else
		newJsrCommand.cBitField.encodingType = Relocatable;
	newJsrCommand.cBitField.destinationOperandAddressing = Direct;
	newJsrCommand.cBitField.opcode = opcodesArray[7].opcodeNum;

	cpuFullMemory[IC].fullReg = newJsrCommand.fullCommandInt;
	IC++;

	DesinationSymbolParam.fullSymbolParam = 0;
	DesinationSymbolParam.symParam.encodingType = External;
	DesinationSymbolParam.symParam.addressValue = data.symbolDestination->addresse;

	cpuFullMemory[IC].fullReg = DesinationSymbolParam.fullSymbolParam;
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

