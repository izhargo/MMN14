#include "SharedHeaderFile.h"
#include "SecondTransitionHeader.h"

char* tabArray = "\t";

cmd movs[] = 
{
	{TWO_REGISTER,movTwoRegisterCmd},
	{REGISTER_SYMBOL,movRegisterSymbolCmd},
	{REGISTER_MATRIX,movRegisterMatrixCmd},
	{MATRIX_REGISTER,movMatrixRegisterCmd},
	{SYMBOL_REGISTER,movSymbolRegisterCmd},
	{SYMBOL_MATRIX,movSymbolMatrixCmd},
	{MATRIX_SYMBOL,movMatrixSymbolCmd},
	{SYMBOL_SYMBOL,movSymbolSymbolCmd},
	{MATRIX_MATRIX,movMatrixMatrixCmd},
	{VALUE_REGISTER,movValueRegisterCmd},
	{VALUE_SYMBOL,movValueSymbolCmd},
	{VALUE_MATRIX,movValueMatrixCmd}
};


cmd cmps[] = 
{
	{TWO_REGISTER,cmpTwoRegisterCmd},
	{REGISTER_SYMBOL,cmpRegisterSymbolCmd},
	{REGISTER_MATRIX,cmpRegisterMatrixCmd},
	{MATRIX_REGISTER,cmpMatrixRegisterCmd},
	{SYMBOL_REGISTER,cmpSymbolRegisterCmd},
	{SYMBOL_MATRIX,cmpSymbolMatrixCmd},
	{MATRIX_SYMBOL,cmpMatrixSymbolCmd},
	{SYMBOL_SYMBOL,cmpSymbolSymbolCmd},
	{MATRIX_MATRIX,cmpMatrixMatrixCmd},
	{VALUE_REGISTER,cmpValueRegisterCmd},
	{VALUE_SYMBOL,cmpValueSymbolCmd},
	{VALUE_MATRIX,cmpValueMatrixCmd}
};

cmd adds[] = 
{
	{TWO_REGISTER,addTwoRegisterCmd},
	{REGISTER_SYMBOL,addRegisterSymbolCmd},
	{REGISTER_MATRIX,addRegisterMatrixCmd},
	{MATRIX_REGISTER,addMatrixRegisterCmd},
	{SYMBOL_REGISTER,addSymbolRegisterCmd},
	{SYMBOL_MATRIX,addSymbolMatrixCmd},
	{MATRIX_SYMBOL,addMatrixSymbolCmd},
	{SYMBOL_SYMBOL,addSymbolSymbolCmd},
	{MATRIX_MATRIX,addMatrixMatrixCmd},
	{VALUE_REGISTER,addValueRegisterCmd},
	{VALUE_SYMBOL,addValueSymbolCmd},
	{VALUE_MATRIX,addValueMatrixCmd}
};

cmd subs[] = 
{
	{TWO_REGISTER,subTwoRegisterCmd},
	{REGISTER_SYMBOL,subRegisterSymbolCmd},
	{REGISTER_MATRIX,subRegisterMatrixCmd},
	{MATRIX_REGISTER,subMatrixRegisterCmd},
	{SYMBOL_REGISTER,subSymbolRegisterCmd},
	{SYMBOL_MATRIX,subSymbolMatrixCmd},
	{MATRIX_SYMBOL,subMatrixSymbolCmd},
	{SYMBOL_SYMBOL,subSymbolSymbolCmd},
	{MATRIX_MATRIX,subMatrixMatrixCmd},
	{VALUE_REGISTER,subValueRegisterCmd},
	{VALUE_SYMBOL,subValueSymbolCmd},
	{VALUE_MATRIX,subValueMatrixCmd}
};

cmd leas[] = 
{
	{TWO_REGISTER,leaTwoRegisterCmd},
	{REGISTER_SYMBOL,leaRegisterSymbolCmd},
	{REGISTER_MATRIX,leaRegisterMatrixCmd},
	{MATRIX_REGISTER,leaMatrixRegisterCmd},
	{SYMBOL_REGISTER,leaSymbolRegisterCmd},
	{SYMBOL_MATRIX,leaSymbolMatrixCmd},
	{MATRIX_SYMBOL,leaMatrixSymbolCmd},
	{SYMBOL_SYMBOL,leaSymbolSymbolCmd},
	{MATRIX_MATRIX,leaMatrixMatrixCmd},
	{VALUE_REGISTER,leaValueRegisterCmd},
	{VALUE_SYMBOL,leaValueSymbolCmd},
	{VALUE_MATRIX,leaValueMatrixCmd}
};

cmd nots[] =
{
	{ONE_REGISTER,notRegisterCmd},
	{ONE_SYMBOL,notSymbolCmd},
	{ONE_MATRIX,notMatrixCmd}
};

cmd clrs[] =
{
	{ONE_REGISTER,clrRegisterCmd},
	{ONE_SYMBOL,clrSymbolCmd},
	{ONE_MATRIX,clrMatrixCmd}
};

cmd incs[] =
{
	{ONE_REGISTER,incRegisterCmd},
	{ONE_SYMBOL,incSymbolCmd},
	{ONE_MATRIX,incMatrixCmd}
};

cmd decs[] =
{
	{ONE_REGISTER,decRegisterCmd},
	{ONE_SYMBOL,decSymbolCmd},
	{ONE_MATRIX,decMatrixCmd}
};

cmd jmps[] =
{
	{ONE_REGISTER,jmpRegisterCmd},
	{ONE_SYMBOL,jmpSymbolCmd},
	{ONE_MATRIX,jmpMatrixCmd}
};

cmd bnes[] =
{
	{ONE_REGISTER,bneRegisterCmd},
	{ONE_SYMBOL,bneSymbolCmd},
	{ONE_MATRIX,bneMatrixCmd}
};

cmd reds[] =
{
	{ONE_REGISTER,redRegisterCmd},
	{ONE_SYMBOL,redSymbolCmd},
	{ONE_MATRIX,redMatrixCmd}
};

cmd prns[] =
{
	{ONE_REGISTER,prnRegisterCmd},
	{ONE_SYMBOL,prnSymbolCmd},
	{ONE_MATRIX,prnMatrixCmd}
};

cmd jsrs[] =
{
	{ONE_REGISTER,jsrRegisterCmd},
	{ONE_SYMBOL,jsrSymbolCmd},
	{ONE_MATRIX,jsrMatrixCmd}
};

cmd rtss[] =
{
	{NONE_PARAMETERS,rtsCmd}
};

cmd stops[] =
{
	{NONE_PARAMETERS,StopCmd}
};

/*A function to readdress all the symbols address in the symbol table*/
void readdressSymbolTable()
{
	int DC_Index = 0;
	pSymbol current = SymbolTable;
	while(current)
	{
		if(current->external == 0 && current->action == 0)
		{
			current->address += IC;
		}
		current = current->next;
	}
	for(DC_Index = 0; DC_Index <= DC; DC_Index++)
	{
		cpuFullMemory[DC_Index+IC] = dataArray[DC_Index];
	}
}

/*A function to add to the memory a mov command with a register as its source parameter and a register as its destination parameter*/
void movTwoRegisterCmd(parms data)
{
	commandBitField newMovCommand;
	registersParam srcDstRegistersParam;

	newMovCommand.fullCommandInt = 0;
	newMovCommand.cBitField.encodingType = Absolute;
	newMovCommand.cBitField.sourceOperandAddressing = DirectRegister;
	newMovCommand.cBitField.destinationOperandAddressing = DirectRegister;
	newMovCommand.cBitField.opcode = opcodesArray[0].opcodeNum;

	cpuFullMemory[IC].fullReg = newMovCommand.fullCommandInt;
	IC++;

	srcDstRegistersParam.fullRegParam = 0;
	srcDstRegistersParam.regParam.encodingType = Absolute;
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

	newMovCommand.cBitField.sourceOperandAddressing = DirectRegister;
	newMovCommand.cBitField.destinationOperandAddressing = Direct;
	newMovCommand.cBitField.opcode = opcodesArray[0].opcodeNum;
	newMovCommand.cBitField.encodingType = Absolute;
	cpuFullMemory[IC].fullReg = newMovCommand.fullCommandInt;
	IC++;

	sourceRegisterParam.fullRegParam = 0;
	sourceRegisterParam.regParam.encodingType = Absolute;
	sourceRegisterParam.regParam.regSource = data.eRegSource;

	cpuFullMemory[IC].fullReg = sourceRegisterParam.fullRegParam;
	IC++;

	destinationSymbolParam.fullSymbolParam = 0;	
	if(data.symbolDestination->external)
	{
		destinationSymbolParam.symParam.encodingType = External;
		addToExternFile(data.symbolDestination);
	}
	else
		destinationSymbolParam.symParam.encodingType = Relocatable;
	destinationSymbolParam.symParam.addressValue = data.symbolDestination->address;

	cpuFullMemory[IC].fullReg = destinationSymbolParam.fullSymbolParam;
	IC++;
}

/*A function to add to the memory a mov command with a register as its source parameter and a matrix parameter as its destination parameter*/
void movRegisterMatrixCmd(parms data)
{
	commandBitField newMovCommand;
	registersParam sourceRegisterParam;
	symbolParam DesinationMatrixParam;
	registersParam DestinationMatrixRegisterParam;

	newMovCommand.fullCommandInt = 0;

	newMovCommand.cBitField.sourceOperandAddressing = DirectRegister;
	newMovCommand.cBitField.destinationOperandAddressing = MatrixAccess;
	newMovCommand.cBitField.opcode = opcodesArray[0].opcodeNum;
	newMovCommand.cBitField.encodingType = Absolute;
	cpuFullMemory[IC].fullReg = newMovCommand.fullCommandInt;
	IC++;

	sourceRegisterParam.fullRegParam = 0;
	sourceRegisterParam.regParam.encodingType = Absolute;
	sourceRegisterParam.regParam.regSource = data.eRegSource;

	cpuFullMemory[IC].fullReg = sourceRegisterParam.fullRegParam;
	IC++;

	DesinationMatrixParam.fullSymbolParam = 0;
	if(data.matrixDestination->external)
		DesinationMatrixParam.symParam.encodingType = External;
	else
		DesinationMatrixParam.symParam.encodingType = Relocatable;
	DesinationMatrixParam.symParam.addressValue = data.matrixDestination->address;

	cpuFullMemory[IC].fullReg = DesinationMatrixParam.fullSymbolParam;
	IC++;

	DestinationMatrixRegisterParam.fullRegParam = 0;
	DestinationMatrixRegisterParam.regParam.encodingType = Absolute;
	DestinationMatrixRegisterParam.regParam.regSource = data.eMatrixRegRowDestination;
	DestinationMatrixRegisterParam.regParam.regDestination = data.eMatrixRegColumnDestination;

	cpuFullMemory[IC].fullReg = DestinationMatrixRegisterParam.fullRegParam;
	IC++;
}

/*A function to add to the memory a mov command with a matrix paramater as its source parameter and a register as its destination parameter*/
void movMatrixRegisterCmd(parms data)
{
	commandBitField newMovCommand;
	symbolParam SourceMatrixParam;
	registersParam SourceMatrixRegisterParam;
	registersParam destinationRegisterParam;

	newMovCommand.fullCommandInt = 0;
	newMovCommand.cBitField.encodingType = Absolute;
	newMovCommand.cBitField.sourceOperandAddressing = MatrixAccess;
	newMovCommand.cBitField.destinationOperandAddressing = DirectRegister;
	newMovCommand.cBitField.opcode = opcodesArray[0].opcodeNum;

	cpuFullMemory[IC].fullReg = newMovCommand.fullCommandInt;
	IC++;

	SourceMatrixParam.fullSymbolParam = 0;
	if(data.matrixSource->external)
		SourceMatrixParam.symParam.encodingType = External;
	else
		SourceMatrixParam.symParam.encodingType = Relocatable;
	SourceMatrixParam.symParam.addressValue = data.matrixSource->address;

	cpuFullMemory[IC].fullReg = SourceMatrixParam.fullSymbolParam;
	IC++;

	SourceMatrixRegisterParam.fullRegParam = 0;
	SourceMatrixRegisterParam.regParam.encodingType = Absolute;
	SourceMatrixRegisterParam.regParam.regSource = data.eMatrixRegRowSource;
	SourceMatrixRegisterParam.regParam.regDestination = data.eMatrixRegColumnSource;

	cpuFullMemory[IC].fullReg = SourceMatrixRegisterParam.fullRegParam;
	IC++;
	
	destinationRegisterParam.fullRegParam = 0;
	destinationRegisterParam.regParam.encodingType = Absolute;
	destinationRegisterParam.regParam.regDestination = data.eRegDestination;

	cpuFullMemory[IC].fullReg = destinationRegisterParam.fullRegParam;
	IC++;
}

/*A function to add to the memory a mov command with a symbol paramater as its source parameter and a register as its destination parameter*/
void movSymbolRegisterCmd(parms data)
{
	commandBitField newMovCommand;
	symbolParam sourceSymbolParam;
	registersParam destinationRegisterParam;

	newMovCommand.fullCommandInt = 0;
	newMovCommand.cBitField.encodingType = Absolute;
	newMovCommand.cBitField.sourceOperandAddressing = Direct;
	newMovCommand.cBitField.destinationOperandAddressing = DirectRegister;
	newMovCommand.cBitField.opcode = opcodesArray[0].opcodeNum;

	cpuFullMemory[IC].fullReg = newMovCommand.fullCommandInt;
	IC++;

	sourceSymbolParam.fullSymbolParam = 0;
	if(data.symbolSource->external)
	{
		sourceSymbolParam.symParam.encodingType = External;
		addToExternFile(data.symbolSource);
	}
	else
		sourceSymbolParam.symParam.encodingType = Relocatable;
	sourceSymbolParam.symParam.addressValue = data.symbolSource->address;

	cpuFullMemory[IC].fullReg = sourceSymbolParam.fullSymbolParam;
	IC++;
	
	destinationRegisterParam.fullRegParam = 0;
	destinationRegisterParam.regParam.encodingType = Absolute;
	destinationRegisterParam.regParam.regDestination = data.eRegDestination;

	cpuFullMemory[IC].fullReg = destinationRegisterParam.fullRegParam;
	IC++;
}

/*A function to add to the memory a mov command with a symbol paramater as its source parameter and a matrix parameter as its destination parameter*/
void movSymbolMatrixCmd(parms data)
{
	commandBitField newMovCommand;
	symbolParam sourceSymbolParam;
	symbolParam DesinationMatrixParam;
	registersParam DestinationMatrixRegisterParam;

	newMovCommand.fullCommandInt = 0;
	newMovCommand.cBitField.encodingType = Absolute;
	newMovCommand.cBitField.sourceOperandAddressing = Direct;
	newMovCommand.cBitField.destinationOperandAddressing = MatrixAccess;
	newMovCommand.cBitField.opcode = opcodesArray[0].opcodeNum;

	cpuFullMemory[IC].fullReg = newMovCommand.fullCommandInt;
	IC++;

	sourceSymbolParam.fullSymbolParam = 0;
	if(data.symbolSource->external)
	{
		sourceSymbolParam.symParam.encodingType = External;
		addToExternFile(data.symbolSource);
	}
	else
		sourceSymbolParam.symParam.encodingType = Relocatable;
	sourceSymbolParam.symParam.addressValue = data.symbolSource->address;

	cpuFullMemory[IC].fullReg = sourceSymbolParam.fullSymbolParam;
	IC++;
	
	DesinationMatrixParam.fullSymbolParam = 0;
	if(data.matrixDestination->external)
		DesinationMatrixParam.symParam.encodingType = External;
	else
		DesinationMatrixParam.symParam.encodingType = Relocatable;
	DesinationMatrixParam.symParam.addressValue = data.matrixDestination->address;

	cpuFullMemory[IC].fullReg = DesinationMatrixParam.fullSymbolParam;
	IC++;

	DestinationMatrixRegisterParam.fullRegParam = 0;
	DestinationMatrixRegisterParam.regParam.encodingType = Absolute;
	DestinationMatrixRegisterParam.regParam.regSource = data.eMatrixRegRowDestination;
	DestinationMatrixRegisterParam.regParam.regDestination = data.eMatrixRegColumnDestination;

	cpuFullMemory[IC].fullReg = DestinationMatrixRegisterParam.fullRegParam;
	IC++;
}

/*A function to add to the memory a mov command a matrix paramater as its source parameter and a symbol parameter as its destination parameter*/
void movMatrixSymbolCmd(parms data)
{
	commandBitField newMovCommand;
	symbolParam SourceMatrixParam;
	registersParam SourceMatrixRegisterParam;
	symbolParam DesinationSymbolParam;

	newMovCommand.fullCommandInt = 0;
	newMovCommand.cBitField.encodingType = Absolute;
	newMovCommand.cBitField.sourceOperandAddressing = MatrixAccess;
	newMovCommand.cBitField.destinationOperandAddressing = Direct;
	newMovCommand.cBitField.opcode = opcodesArray[0].opcodeNum;

	cpuFullMemory[IC].fullReg = newMovCommand.fullCommandInt;
	IC++;

	SourceMatrixParam.fullSymbolParam = 0;
	if(data.matrixSource->external)
	{
		SourceMatrixParam.symParam.encodingType = External;
		addToExternFile(data.matrixSource);
	}
	else
		SourceMatrixParam.symParam.encodingType = Relocatable;
	SourceMatrixParam.symParam.addressValue = data.matrixSource->address;

	cpuFullMemory[IC].fullReg = SourceMatrixParam.fullSymbolParam;
	IC++;

	SourceMatrixRegisterParam.fullRegParam = 0;
	SourceMatrixRegisterParam.regParam.encodingType = Absolute;
	SourceMatrixRegisterParam.regParam.regSource = data.eMatrixRegRowSource;
	SourceMatrixRegisterParam.regParam.regDestination = data.eMatrixRegColumnSource;

	cpuFullMemory[IC].fullReg = SourceMatrixRegisterParam.fullRegParam;
	IC++;
	
	DesinationSymbolParam.fullSymbolParam = 0;
	if(data.symbolDestination->external)
	{
		DesinationSymbolParam.symParam.encodingType = External;
		addToExternFile(data.symbolDestination);
	}
	else
		DesinationSymbolParam.symParam.encodingType = Relocatable;
	DesinationSymbolParam.symParam.addressValue = data.symbolDestination->address;

	cpuFullMemory[IC].fullReg = DesinationSymbolParam.fullSymbolParam;
	IC++;
}

/*A function to add to the memory a mov command a symbol paramater as its source parameter and a symbol parameter as its destination parameter*/
void movSymbolSymbolCmd(parms data)
{
	commandBitField newMovCommand;
	symbolParam SourceSymbolParam;
	symbolParam DesinationSymbolParam;
	
	newMovCommand.fullCommandInt = 0;
	newMovCommand.cBitField.encodingType = Absolute;
	newMovCommand.cBitField.sourceOperandAddressing = Direct;
	newMovCommand.cBitField.destinationOperandAddressing = Direct;
	newMovCommand.cBitField.opcode = opcodesArray[0].opcodeNum;

	cpuFullMemory[IC].fullReg = newMovCommand.fullCommandInt;
	IC++;

	SourceSymbolParam.fullSymbolParam = 0;
	if(data.symbolSource->external)
	{
		SourceSymbolParam.symParam.encodingType = External;
		addToExternFile(data.symbolSource);
	}
	else
		SourceSymbolParam.symParam.encodingType = Relocatable;
	SourceSymbolParam.symParam.addressValue = data.symbolSource->address;

	cpuFullMemory[IC].fullReg = SourceSymbolParam.fullSymbolParam;
	IC++;
	
	DesinationSymbolParam.fullSymbolParam = 0;
	if(data.symbolDestination->external)
	{
		DesinationSymbolParam.symParam.encodingType = External;
		addToExternFile(data.symbolDestination);
	}
	else
		DesinationSymbolParam.symParam.encodingType = Relocatable;
	DesinationSymbolParam.symParam.addressValue = data.symbolDestination->address;

	cpuFullMemory[IC].fullReg = DesinationSymbolParam.fullSymbolParam;
	IC++;
}

/*A function to add to the memory a mov command a matrix paramater as its source parameter and a matrix parameter as its destination parameter*/
void movMatrixMatrixCmd(parms data)
{
	commandBitField newMovCommand;
	symbolParam SourceMatrixParam;
	registersParam SourceMatrixRegisterParam;
	symbolParam DesinationMatrixParam;
	registersParam DestinationMatrixRegisterParam;

	newMovCommand.fullCommandInt = 0;
	newMovCommand.cBitField.encodingType = Absolute;
	newMovCommand.cBitField.sourceOperandAddressing = MatrixAccess;
	newMovCommand.cBitField.destinationOperandAddressing = MatrixAccess;
	newMovCommand.cBitField.opcode = opcodesArray[0].opcodeNum;

	cpuFullMemory[IC].fullReg = newMovCommand.fullCommandInt;
	IC++;

	SourceMatrixParam.fullSymbolParam = 0;
	if(data.matrixSource->external)
	{
		SourceMatrixParam.symParam.encodingType = External;
		addToExternFile(data.matrixSource);
	}
	else
		SourceMatrixParam.symParam.encodingType = Relocatable;
	SourceMatrixParam.symParam.addressValue = data.matrixSource->address;

	cpuFullMemory[IC].fullReg = SourceMatrixParam.fullSymbolParam;
	IC++;

	SourceMatrixRegisterParam.fullRegParam = 0;
	SourceMatrixRegisterParam.regParam.encodingType = Absolute;
	SourceMatrixRegisterParam.regParam.regSource = data.eMatrixRegRowSource;
	SourceMatrixRegisterParam.regParam.regDestination = data.eMatrixRegColumnSource;

	cpuFullMemory[IC].fullReg = SourceMatrixRegisterParam.fullRegParam;
	IC++;
	
	DesinationMatrixParam.fullSymbolParam = 0;
	if(data.matrixDestination->external)
	{
		DesinationMatrixParam.symParam.encodingType = External;
		addToExternFile(data.matrixDestination);
	}
	else
		DesinationMatrixParam.symParam.encodingType = Relocatable;
	DesinationMatrixParam.symParam.addressValue = data.matrixDestination->address;

	cpuFullMemory[IC].fullReg = DesinationMatrixParam.fullSymbolParam;
	IC++;

	DestinationMatrixRegisterParam.fullRegParam = 0;
	DestinationMatrixRegisterParam.regParam.encodingType = Absolute;
	DestinationMatrixRegisterParam.regParam.regSource = data.eMatrixRegRowDestination;
	DestinationMatrixRegisterParam.regParam.regDestination = data.eMatrixRegColumnDestination;

	cpuFullMemory[IC].fullReg = DestinationMatrixRegisterParam.fullRegParam;
	IC++;
}

/*A function to add to the memory a mov command with a numeric value as its source parameter and a register as its destination parameter*/
void movValueRegisterCmd(parms data)
{
	commandBitField newMovCommand;
	valueParam sourceValueParam;
	registersParam destinationRegisterParam;

	newMovCommand.fullCommandInt = 0;
	newMovCommand.cBitField.encodingType = Absolute;
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
	destinationRegisterParam.regParam.encodingType = Absolute;
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
	newMovCommand.cBitField.encodingType = Absolute;
	newMovCommand.cBitField.sourceOperandAddressing = Immediate;
	newMovCommand.cBitField.destinationOperandAddressing = Direct;
	newMovCommand.cBitField.opcode = opcodesArray[0].opcodeNum;

	cpuFullMemory[IC].fullReg = newMovCommand.fullCommandInt;
	IC++;

	sourceValueParam.fullValueParam = 0;
	sourceValueParam.valParam.encodingType = Absolute;
	sourceValueParam.valParam.numericValue = data.sourceNum;

	cpuFullMemory[IC].fullReg = sourceValueParam.fullValueParam;
	IC++;
	
	DesinationSymbolParam.fullSymbolParam = 0;
	if(data.symbolDestination->external)
	{
		DesinationSymbolParam.symParam.encodingType  = External;
		addToExternFile(data.symbolDestination);
	}
	else
		DesinationSymbolParam.symParam.encodingType  = Relocatable;
	DesinationSymbolParam.symParam.addressValue = data.symbolDestination->address;

	cpuFullMemory[IC].fullReg = DesinationSymbolParam.fullSymbolParam;
	IC++;
}

/*A function to add to the memory a mov command with a numeric value as its source parameter and a matrix parameter as its destination parameter*/
void movValueMatrixCmd(parms data)
{
	commandBitField newMovCommand;
	valueParam sourceValueParam;
	symbolParam DesinationMatrixParam;
	registersParam DestinationMatrixRegisterParam;

	newMovCommand.fullCommandInt = 0;
	newMovCommand.cBitField.encodingType = Absolute;
	newMovCommand.cBitField.sourceOperandAddressing = Immediate;
	newMovCommand.cBitField.destinationOperandAddressing = MatrixAccess;
	newMovCommand.cBitField.opcode = opcodesArray[0].opcodeNum;

	cpuFullMemory[IC].fullReg = newMovCommand.fullCommandInt;
	IC++;

	sourceValueParam.fullValueParam = 0;
	sourceValueParam.valParam.encodingType = Absolute;
	sourceValueParam.valParam.numericValue = data.sourceNum;

	cpuFullMemory[IC].fullReg = sourceValueParam.fullValueParam;
	IC++;
	
	DesinationMatrixParam.fullSymbolParam = 0;
	if(data.matrixDestination->external)
	{
		DesinationMatrixParam.symParam.encodingType = External;
		addToExternFile(data.matrixDestination);
	}
	else
		DesinationMatrixParam.symParam.encodingType = Relocatable;
	DesinationMatrixParam.symParam.addressValue = data.matrixDestination->address;

	cpuFullMemory[IC].fullReg = DesinationMatrixParam.fullSymbolParam;
	IC++;

	DestinationMatrixRegisterParam.fullRegParam = 0;
	DestinationMatrixRegisterParam.regParam.encodingType = Absolute;
	DestinationMatrixRegisterParam.regParam.regSource = data.eMatrixRegRowDestination;
	DestinationMatrixRegisterParam.regParam.regDestination = data.eMatrixRegColumnDestination;

	cpuFullMemory[IC].fullReg = DestinationMatrixRegisterParam.fullRegParam;
	IC++;
}

/*A function to add to the memory a cmp command with a numeric value as its source parameter and a numeric value as its destination parameter*/
void cmpValueValueCmd(parms data)
{
	commandBitField newCmpCommand;
	valueParam sourceValueParam;
	valueParam destinationValueParam;

	newCmpCommand.fullCommandInt = 0;
	newCmpCommand.cBitField.encodingType = Absolute;
	newCmpCommand.cBitField.sourceOperandAddressing = Immediate;
	newCmpCommand.cBitField.destinationOperandAddressing = Immediate;
	newCmpCommand.cBitField.opcode = opcodesArray[1].opcodeNum;

	cpuFullMemory[IC].fullReg = newCmpCommand.fullCommandInt;
	IC++;

	sourceValueParam.fullValueParam = 0;
	sourceValueParam.valParam.encodingType = Absolute;
	sourceValueParam.valParam.numericValue = data.sourceNum;

	cpuFullMemory[IC].fullReg = sourceValueParam.fullValueParam;
	IC++;

	destinationValueParam.fullValueParam = 0;
	destinationValueParam.valParam.encodingType = Absolute;
	destinationValueParam.valParam.numericValue = data.destinationNum;

	cpuFullMemory[IC].fullReg = destinationValueParam.fullValueParam;
	IC++;
}

/*A function to add to the memory a cmp command with a register as its source parameter and a numeric value as its destination parameter*/
void cmpRegisterValueCmd(parms data)
{
	commandBitField newCmpCommand;
	registersParam sourceRegisterParam;
	valueParam destinationValueParam;

	newCmpCommand.fullCommandInt = 0;
	newCmpCommand.cBitField.encodingType = Absolute;
	newCmpCommand.cBitField.sourceOperandAddressing = DirectRegister;
	newCmpCommand.cBitField.destinationOperandAddressing = Immediate;
	newCmpCommand.cBitField.opcode = opcodesArray[1].opcodeNum;

	cpuFullMemory[IC].fullReg = newCmpCommand.fullCommandInt;
	IC++;

	sourceRegisterParam.fullRegParam = 0;
	sourceRegisterParam.regParam.encodingType = Absolute;
	sourceRegisterParam.regParam.regSource = data.eRegSource;

	cpuFullMemory[IC].fullReg = sourceRegisterParam.fullRegParam;
	IC++;

	destinationValueParam.fullValueParam = 0;
	destinationValueParam.valParam.encodingType = Absolute;
	destinationValueParam.valParam.numericValue = data.destinationNum;

	cpuFullMemory[IC].fullReg = destinationValueParam.fullValueParam;
	IC++;
}

/*A function to add to the memory a cmp command with a symbol parameter as its source parameter and a numeric value as its destination parameter*/
void cmpSymbolValueCmd(parms data)
{
	commandBitField newCmpCommand;
	symbolParam sourceSymbolParam;
	valueParam destinationValueParam;

	newCmpCommand.fullCommandInt = 0;
	newCmpCommand.cBitField.encodingType = Absolute;
	newCmpCommand.cBitField.sourceOperandAddressing = Direct;
	newCmpCommand.cBitField.destinationOperandAddressing = Immediate;
	newCmpCommand.cBitField.opcode = opcodesArray[1].opcodeNum;

	cpuFullMemory[IC].fullReg = newCmpCommand.fullCommandInt;
	IC++;

	sourceSymbolParam.fullSymbolParam = 0;
	if(data.symbolSource->external)
	{
		sourceSymbolParam.symParam.encodingType = External;
		addToExternFile(data.symbolSource);
	}
	else
		sourceSymbolParam.symParam.encodingType = Relocatable;
	sourceSymbolParam.symParam.addressValue = data.symbolSource->address;

	cpuFullMemory[IC].fullReg = sourceSymbolParam.fullSymbolParam;
	IC++;

	destinationValueParam.fullValueParam = 0;
	destinationValueParam.valParam.encodingType = Absolute;
	destinationValueParam.valParam.numericValue = data.destinationNum;

	cpuFullMemory[IC].fullReg = destinationValueParam.fullValueParam;
	IC++;
}

/*A function to add to the memory a cmp command with a matrix parameter as its source parameter and a numeric value as its destination parameter*/
void cmpMatrixValueCmd(parms data)
{
	commandBitField newCmpCommand;
	symbolParam SourceMatrixParam;
	registersParam SourceMatrixRegisterParam;
	valueParam destinationValueParam;

	newCmpCommand.fullCommandInt = 0;
	newCmpCommand.cBitField.encodingType = Absolute;
	newCmpCommand.cBitField.sourceOperandAddressing = Direct;
	newCmpCommand.cBitField.destinationOperandAddressing = Immediate;
	newCmpCommand.cBitField.opcode = opcodesArray[1].opcodeNum;

	cpuFullMemory[IC].fullReg = newCmpCommand.fullCommandInt;
	IC++;

	SourceMatrixParam.fullSymbolParam = 0;
	if(data.matrixSource->external)
	{
		SourceMatrixParam.symParam.encodingType = External;
		addToExternFile(data.matrixSource);
	}
	else
		SourceMatrixParam.symParam.encodingType = Relocatable;
	SourceMatrixParam.symParam.addressValue = data.matrixSource->address;

	cpuFullMemory[IC].fullReg = SourceMatrixParam.fullSymbolParam;
	IC++;

	SourceMatrixRegisterParam.fullRegParam = 0;
	SourceMatrixRegisterParam.regParam.encodingType = Absolute;
	SourceMatrixRegisterParam.regParam.regSource = data.eMatrixRegRowSource;
	SourceMatrixRegisterParam.regParam.regDestination = data.eMatrixRegColumnSource;

	cpuFullMemory[IC].fullReg = SourceMatrixRegisterParam.fullRegParam;
	IC++;

	destinationValueParam.fullValueParam = 0;
	destinationValueParam.valParam.encodingType = Absolute;
	destinationValueParam.valParam.numericValue = data.destinationNum;

	cpuFullMemory[IC].fullReg = destinationValueParam.fullValueParam;
	IC++;
}

/*A function to add to the memory a cmp command with a register as its source parameter and a register as its destination parameter*/
void cmpTwoRegisterCmd(parms data)
{
	commandBitField newCmpCommand;
	registersParam srcDstRegistersParam;

	newCmpCommand.fullCommandInt = 0;
	newCmpCommand.cBitField.encodingType = Absolute;
	newCmpCommand.cBitField.sourceOperandAddressing = DirectRegister;
	newCmpCommand.cBitField.destinationOperandAddressing = DirectRegister;
	newCmpCommand.cBitField.opcode = opcodesArray[1].opcodeNum;

	cpuFullMemory[IC].fullReg = newCmpCommand.fullCommandInt;
	IC++;

	srcDstRegistersParam.fullRegParam = 0;
	srcDstRegistersParam.regParam.encodingType = Absolute;
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
	newCmpCommand.cBitField.encodingType = Absolute;
	newCmpCommand.cBitField.sourceOperandAddressing = DirectRegister;
	newCmpCommand.cBitField.destinationOperandAddressing = Direct;
	newCmpCommand.cBitField.opcode = opcodesArray[1].opcodeNum;

	cpuFullMemory[IC].fullReg = newCmpCommand.fullCommandInt;
	IC++;

	sourceRegisterParam.fullRegParam = 0;
	sourceRegisterParam.regParam.encodingType = Absolute;
	sourceRegisterParam.regParam.regSource = data.eRegSource;

	cpuFullMemory[IC].fullReg = sourceRegisterParam.fullRegParam;
	IC++;

	destinationSymbolParam.fullSymbolParam = 0;
	if(data.symbolDestination->external)
	{
		destinationSymbolParam.symParam.encodingType = External;
		addToExternFile(data.symbolDestination);
	}
	else
		destinationSymbolParam.symParam.encodingType = Relocatable;
	destinationSymbolParam.symParam.addressValue = data.symbolDestination->address;

	cpuFullMemory[IC].fullReg = destinationSymbolParam.fullSymbolParam;
	IC++;
}

/*A function to add to the memory a cmp command with a register as its source parameter and a matrix parameter as its destination parameter*/
void cmpRegisterMatrixCmd(parms data)
{
	commandBitField newCmpCommand;
	registersParam sourceRegisterParam;
	symbolParam DesinationMatrixParam;
	registersParam DestinationMatrixRegisterParam;

	newCmpCommand.fullCommandInt = 0;
	newCmpCommand.cBitField.encodingType = Absolute;
	newCmpCommand.cBitField.sourceOperandAddressing = DirectRegister;
	newCmpCommand.cBitField.destinationOperandAddressing = MatrixAccess;
	newCmpCommand.cBitField.opcode = opcodesArray[1].opcodeNum;

	cpuFullMemory[IC].fullReg = newCmpCommand.fullCommandInt;
	IC++;

	sourceRegisterParam.fullRegParam = 0;
	sourceRegisterParam.regParam.encodingType = Absolute;
	sourceRegisterParam.regParam.regSource = data.eRegSource;

	cpuFullMemory[IC].fullReg = sourceRegisterParam.fullRegParam;
	IC++;

	DesinationMatrixParam.fullSymbolParam = 0;
	if(data.matrixDestination->external)
	{
		DesinationMatrixParam.symParam.encodingType = External;
		addToExternFile(data.matrixDestination);
	}
	else
		DesinationMatrixParam.symParam.encodingType = Relocatable;
	DesinationMatrixParam.symParam.addressValue = data.matrixDestination->address;

	cpuFullMemory[IC].fullReg = DesinationMatrixParam.fullSymbolParam;
	IC++;

	DestinationMatrixRegisterParam.fullRegParam = 0;
	DestinationMatrixRegisterParam.regParam.encodingType = Absolute;
	DestinationMatrixRegisterParam.regParam.regSource = data.eMatrixRegRowDestination;
	DestinationMatrixRegisterParam.regParam.regDestination = data.eMatrixRegColumnDestination;

	cpuFullMemory[IC].fullReg = DestinationMatrixRegisterParam.fullRegParam;
	IC++;
}

/*A function to add to the memory a cmp command with a matrix paramater as its source parameter and a register as its destination parameter*/
void cmpMatrixRegisterCmd(parms data)
{
	commandBitField newCmpCommand;
	symbolParam SourceMatrixParam;
	registersParam SourceMatrixRegisterParam;
	registersParam destinationRegisterParam;

	newCmpCommand.fullCommandInt = 0;
	newCmpCommand.cBitField.encodingType = Absolute;
	newCmpCommand.cBitField.sourceOperandAddressing = MatrixAccess;
	newCmpCommand.cBitField.destinationOperandAddressing = DirectRegister;
	newCmpCommand.cBitField.opcode = opcodesArray[1].opcodeNum;

	cpuFullMemory[IC].fullReg = newCmpCommand.fullCommandInt;
	IC++;

	SourceMatrixParam.fullSymbolParam = 0;
	if(data.matrixSource->external)
	{
		SourceMatrixParam.symParam.encodingType = External;
		addToExternFile(data.matrixSource);
	}
	else
		SourceMatrixParam.symParam.encodingType = Relocatable;
	SourceMatrixParam.symParam.addressValue = data.matrixSource->address;

	cpuFullMemory[IC].fullReg = SourceMatrixParam.fullSymbolParam;
	IC++;

	SourceMatrixRegisterParam.fullRegParam = 0;
	SourceMatrixRegisterParam.regParam.encodingType = Absolute;
	SourceMatrixRegisterParam.regParam.regSource = data.eMatrixRegRowSource;
	SourceMatrixRegisterParam.regParam.regDestination = data.eMatrixRegColumnSource;

	cpuFullMemory[IC].fullReg = SourceMatrixRegisterParam.fullRegParam;
	IC++;
	
	destinationRegisterParam.fullRegParam = 0;
	destinationRegisterParam.regParam.encodingType = Absolute;
	destinationRegisterParam.regParam.regDestination = data.eRegDestination;

	cpuFullMemory[IC].fullReg = destinationRegisterParam.fullRegParam;
	IC++;
}

/*A function to add to the memory a cmp command with a symbol paramater as its source parameter and a register as its destination parameter*/
void cmpSymbolRegisterCmd(parms data)
{
	commandBitField newCmpCommand;
	symbolParam sourceSymbolParam;
	registersParam destinationRegisterParam;

	newCmpCommand.fullCommandInt = 0;
	newCmpCommand.cBitField.encodingType = Absolute;
	newCmpCommand.cBitField.sourceOperandAddressing = Direct;
	newCmpCommand.cBitField.destinationOperandAddressing = DirectRegister;
	newCmpCommand.cBitField.opcode = opcodesArray[1].opcodeNum;

	cpuFullMemory[IC].fullReg = newCmpCommand.fullCommandInt;
	IC++;

	sourceSymbolParam.fullSymbolParam = 0;
	if(data.symbolSource->external)
	{
		sourceSymbolParam.symParam.encodingType = External;
		addToExternFile(data.symbolSource);
	}
	else
		sourceSymbolParam.symParam.encodingType = Relocatable;
	sourceSymbolParam.symParam.addressValue = data.symbolSource->address;

	cpuFullMemory[IC].fullReg = sourceSymbolParam.fullSymbolParam;
	IC++;
	
	destinationRegisterParam.fullRegParam = 0;
	destinationRegisterParam.regParam.encodingType = Absolute;
	destinationRegisterParam.regParam.regDestination = data.eRegDestination;

	cpuFullMemory[IC].fullReg = destinationRegisterParam.fullRegParam;
	IC++;
}

/*A function to add to the memory a cmp command with a symbol paramater as its source parameter and a matrix parameter as its destination parameter*/
void cmpSymbolMatrixCmd(parms data)
{
	commandBitField newCmpCommand;
	symbolParam SourceSymbolParam;
	symbolParam DesinationMatrixParam;
	registersParam DestinationMatrixRegisterParam;

	newCmpCommand.fullCommandInt = 0;
	newCmpCommand.cBitField.encodingType = Absolute;
	newCmpCommand.cBitField.sourceOperandAddressing = Direct;
	newCmpCommand.cBitField.destinationOperandAddressing = MatrixAccess;
	newCmpCommand.cBitField.opcode = opcodesArray[1].opcodeNum;

	cpuFullMemory[IC].fullReg = newCmpCommand.fullCommandInt;
	IC++;

	SourceSymbolParam.fullSymbolParam = 0;
	if(data.symbolSource->external)
	{
		SourceSymbolParam.symParam.encodingType = External;
		addToExternFile(data.symbolSource);
	}
	else
		SourceSymbolParam.symParam.encodingType = Relocatable;
	SourceSymbolParam.symParam.addressValue = data.symbolSource->address;

	cpuFullMemory[IC].fullReg = SourceSymbolParam.fullSymbolParam;
	IC++;
	
	DesinationMatrixParam.fullSymbolParam = 0;
	if(data.matrixDestination->external)
	{
		DesinationMatrixParam.symParam.encodingType = External;
		addToExternFile(data.matrixDestination);
	}
	else
		DesinationMatrixParam.symParam.encodingType = Relocatable;
	DesinationMatrixParam.symParam.addressValue = data.matrixDestination->address;

	cpuFullMemory[IC].fullReg = DesinationMatrixParam.fullSymbolParam;
	IC++;

	DestinationMatrixRegisterParam.fullRegParam = 0;
	DestinationMatrixRegisterParam.regParam.encodingType = Absolute;
	DestinationMatrixRegisterParam.regParam.regSource = data.eMatrixRegRowDestination;
	DestinationMatrixRegisterParam.regParam.regDestination = data.eMatrixRegColumnDestination;

	cpuFullMemory[IC].fullReg = DestinationMatrixRegisterParam.fullRegParam;
	IC++;
}

/*A function to add to the memory a cmp command with a matrix paramater as its source parameter and a symbol parameter as its destination parameter*/
void cmpMatrixSymbolCmd(parms data)
{
	commandBitField newCmpCommand;
	symbolParam SourceMatrixParam;
	registersParam SourceMatrixRegisterParam;
	symbolParam DesinationSymbolParam;

	newCmpCommand.fullCommandInt = 0;
	newCmpCommand.cBitField.encodingType = Absolute;
	newCmpCommand.cBitField.sourceOperandAddressing = MatrixAccess;
	newCmpCommand.cBitField.destinationOperandAddressing = Direct;
	newCmpCommand.cBitField.opcode = opcodesArray[1].opcodeNum;

	cpuFullMemory[IC].fullReg = newCmpCommand.fullCommandInt;
	IC++;

	SourceMatrixParam.fullSymbolParam = 0;
	if(data.matrixSource->external)
	{
		SourceMatrixParam.symParam.encodingType = External;
		addToExternFile(data.matrixSource);
	}
	else
		SourceMatrixParam.symParam.encodingType = Relocatable;
	SourceMatrixParam.symParam.addressValue = data.matrixSource->address;

	cpuFullMemory[IC].fullReg = SourceMatrixParam.fullSymbolParam;
	IC++;

	SourceMatrixRegisterParam.fullRegParam = 0;
	SourceMatrixRegisterParam.regParam.encodingType = Absolute;
	SourceMatrixRegisterParam.regParam.regSource = data.eMatrixRegRowSource;
	SourceMatrixRegisterParam.regParam.regDestination = data.eMatrixRegColumnSource;

	cpuFullMemory[IC].fullReg = SourceMatrixRegisterParam.fullRegParam;
	IC++;

	DesinationSymbolParam.fullSymbolParam = 0;
	if(data.symbolDestination->external)
	{
		DesinationSymbolParam.symParam.encodingType = External;
		addToExternFile(data.symbolDestination);
	}
	else
		DesinationSymbolParam.symParam.encodingType = Relocatable;
	DesinationSymbolParam.symParam.addressValue = data.symbolDestination->address;

	cpuFullMemory[IC].fullReg = DesinationSymbolParam.fullSymbolParam;
	IC++;
}

/*A function to add to the memory a cmp command with a symbol paramater as its source parameter and a symbol parameter as its destination parameter*/
void cmpSymbolSymbolCmd(parms data)
{
	commandBitField newCmpCommand;
	symbolParam SourceSymbolParam;
	symbolParam DesinationSymbolParam;

	newCmpCommand.fullCommandInt = 0;
	newCmpCommand.cBitField.encodingType = Absolute;
	newCmpCommand.cBitField.sourceOperandAddressing = Direct;
	newCmpCommand.cBitField.destinationOperandAddressing = Direct;
	newCmpCommand.cBitField.opcode = opcodesArray[1].opcodeNum;

	cpuFullMemory[IC].fullReg = newCmpCommand.fullCommandInt;
	IC++;

	SourceSymbolParam.fullSymbolParam = 0;
	if(data.symbolSource->external)
	{
		SourceSymbolParam.symParam.encodingType = External;
		addToExternFile(data.symbolSource);
	}
	else
		SourceSymbolParam.symParam.encodingType = Relocatable;
	SourceSymbolParam.symParam.addressValue = data.symbolSource->address;

	cpuFullMemory[IC].fullReg = SourceSymbolParam.fullSymbolParam;
	IC++;
	
	DesinationSymbolParam.fullSymbolParam = 0;
	if(data.symbolDestination->external)
	{
		DesinationSymbolParam.symParam.encodingType = External;
		addToExternFile(data.symbolDestination);
	}
	else
		DesinationSymbolParam.symParam.encodingType = Relocatable;
	DesinationSymbolParam.symParam.addressValue = data.symbolDestination->address;

	cpuFullMemory[IC].fullReg = DesinationSymbolParam.fullSymbolParam;
	IC++;
}

/*A function to add to the memory a cmp command with a matrix paramater as its source parameter and a matrix parameter as its destination parameter*/
void cmpMatrixMatrixCmd(parms data)
{
	commandBitField newCmpCommand;
	symbolParam SourceMatrixParam;
	registersParam SourceMatrixRegisterParam;
	symbolParam DesinationMatrixParam;
	registersParam DestinationMatrixRegisterParam;

	newCmpCommand.fullCommandInt = 0;
	newCmpCommand.cBitField.encodingType = Absolute;
	newCmpCommand.cBitField.sourceOperandAddressing = MatrixAccess;
	newCmpCommand.cBitField.destinationOperandAddressing = MatrixAccess;
	newCmpCommand.cBitField.opcode = opcodesArray[1].opcodeNum;

	cpuFullMemory[IC].fullReg = newCmpCommand.fullCommandInt;
	IC++;

	SourceMatrixParam.fullSymbolParam = 0;
	if(data.matrixSource->external)
	{
		SourceMatrixParam.symParam.encodingType = External;
		addToExternFile(data.matrixSource);
	}
	else
		SourceMatrixParam.symParam.encodingType = Relocatable;
	SourceMatrixParam.symParam.addressValue = data.matrixSource->address;

	cpuFullMemory[IC].fullReg = SourceMatrixParam.fullSymbolParam;
	IC++;

	SourceMatrixRegisterParam.fullRegParam = 0;
	SourceMatrixRegisterParam.regParam.encodingType = Absolute;
	SourceMatrixRegisterParam.regParam.regSource = data.eMatrixRegRowSource;
	SourceMatrixRegisterParam.regParam.regDestination = data.eMatrixRegColumnSource;

	cpuFullMemory[IC].fullReg = SourceMatrixRegisterParam.fullRegParam;
	IC++;
	
	DesinationMatrixParam.fullSymbolParam = 0;
	if(data.matrixDestination->external)
		DesinationMatrixParam.symParam.encodingType = External;
	else
		DesinationMatrixParam.symParam.encodingType = Relocatable;
	DesinationMatrixParam.symParam.addressValue = data.matrixDestination->address;

	cpuFullMemory[IC].fullReg = DesinationMatrixParam.fullSymbolParam;
	IC++;

	DestinationMatrixRegisterParam.fullRegParam = 0;
	DestinationMatrixRegisterParam.regParam.encodingType = Absolute;
	DestinationMatrixRegisterParam.regParam.regSource = data.eMatrixRegRowDestination;
	DestinationMatrixRegisterParam.regParam.regDestination = data.eMatrixRegColumnDestination;

	cpuFullMemory[IC].fullReg = DestinationMatrixRegisterParam.fullRegParam;
	IC++;
}

/*A function to add to the memory a cmp command with a numeric value as its source parameter and a register as its destination parameter*/
void cmpValueRegisterCmd(parms data)
{
	commandBitField newCmpCommand;	
	valueParam sourceValueParam;
	registersParam destinationRegistersParam;

	newCmpCommand.fullCommandInt = 0;
	newCmpCommand.cBitField.encodingType = Absolute;
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
	destinationRegistersParam.regParam.encodingType = Absolute;
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
	newCmpCommand.cBitField.encodingType = Absolute;
	newCmpCommand.cBitField.sourceOperandAddressing = Immediate;
	newCmpCommand.cBitField.destinationOperandAddressing = Direct;
	newCmpCommand.cBitField.opcode = opcodesArray[1].opcodeNum;

	cpuFullMemory[IC].fullReg = newCmpCommand.fullCommandInt;
	IC++;

	sourceValueParam.fullValueParam = 0;
	sourceValueParam.valParam.encodingType = Absolute;
	sourceValueParam.valParam.numericValue = data.sourceNum;

	cpuFullMemory[IC].fullReg = sourceValueParam.fullValueParam;
	IC++;
	
	DesinationSymbolParam.fullSymbolParam = 0;
	if(data.symbolDestination->external)
	{
		DesinationSymbolParam.symParam.encodingType = External;
		addToExternFile(data.symbolDestination);
	}
	else
		DesinationSymbolParam.symParam.encodingType = Relocatable;
	DesinationSymbolParam.symParam.addressValue = data.symbolDestination->address;

	cpuFullMemory[IC].fullReg = DesinationSymbolParam.fullSymbolParam;
	IC++;
}

/*A function to add to the memory a cmp command with a numeric value as its source parameter and a matrix parameter as its destination parameter*/
void cmpValueMatrixCmd(parms data)
{
	commandBitField newCmpCommand;
	valueParam sourceValueParam;
	symbolParam DesinationMatrixParam;
	registersParam DestinationMatrixRegisterParam;

	newCmpCommand.fullCommandInt = 0;
	newCmpCommand.cBitField.encodingType = Absolute;
	newCmpCommand.cBitField.sourceOperandAddressing = Immediate;
	newCmpCommand.cBitField.destinationOperandAddressing = MatrixAccess;
	newCmpCommand.cBitField.opcode = opcodesArray[1].opcodeNum;

	cpuFullMemory[IC].fullReg = newCmpCommand.fullCommandInt;
	IC++;

	sourceValueParam.fullValueParam = 0;
	sourceValueParam.valParam.encodingType = Absolute;
	sourceValueParam.valParam.numericValue = data.sourceNum;

	cpuFullMemory[IC].fullReg = sourceValueParam.fullValueParam;
	IC++;
	
	DesinationMatrixParam.fullSymbolParam = 0;
	if(data.matrixDestination->external)
	{
		DesinationMatrixParam.symParam.encodingType = External;
		addToExternFile(data.matrixDestination);
	}
	else
		DesinationMatrixParam.symParam.encodingType = Relocatable;
	DesinationMatrixParam.symParam.addressValue = data.matrixDestination->address;

	cpuFullMemory[IC].fullReg = DesinationMatrixParam.fullSymbolParam;
	IC++;

	DestinationMatrixRegisterParam.fullRegParam = 0;
	DestinationMatrixRegisterParam.regParam.encodingType = Absolute;
	DestinationMatrixRegisterParam.regParam.regSource = data.eMatrixRegRowDestination;
	DestinationMatrixRegisterParam.regParam.regDestination = data.eMatrixRegColumnDestination;

	cpuFullMemory[IC].fullReg = DestinationMatrixRegisterParam.fullRegParam;
	IC++;
}

/*A function to add to the memory a add command with a register as its source parameter and a register as its destination parameter*/
void addTwoRegisterCmd(parms data)
{
	commandBitField newAddCommand;
	registersParam srcDstRegistersParam;

	newAddCommand.fullCommandInt = 0;
	newAddCommand.cBitField.encodingType = Absolute;
	newAddCommand.cBitField.sourceOperandAddressing = DirectRegister;
	newAddCommand.cBitField.destinationOperandAddressing = DirectRegister;
	newAddCommand.cBitField.opcode = opcodesArray[2].opcodeNum;

	cpuFullMemory[IC].fullReg = newAddCommand.fullCommandInt;
	IC++;

	srcDstRegistersParam.fullRegParam = 0;
	srcDstRegistersParam.regParam.encodingType = Absolute;
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
	newAddCommand.cBitField.sourceOperandAddressing = Absolute;
	newAddCommand.cBitField.encodingType = DirectRegister;
	newAddCommand.cBitField.destinationOperandAddressing = Direct;
	newAddCommand.cBitField.opcode = opcodesArray[1].opcodeNum;

	cpuFullMemory[IC].fullReg = newAddCommand.fullCommandInt;
	IC++;

	sourceRegisterParam.fullRegParam = 0;
	sourceRegisterParam.regParam.encodingType = Absolute;
	sourceRegisterParam.regParam.regSource = data.eRegSource;

	cpuFullMemory[IC].fullReg = sourceRegisterParam.fullRegParam;
	IC++;

	destinationSymbolParam.fullSymbolParam = 0;
	if(data.symbolDestination->external)
	{
		destinationSymbolParam.symParam.encodingType = External;
		addToExternFile(data.symbolDestination);
	}
	else
		destinationSymbolParam.symParam.encodingType = Relocatable;
	destinationSymbolParam.symParam.addressValue = data.symbolDestination->address;

	cpuFullMemory[IC].fullReg = destinationSymbolParam.fullSymbolParam;
	IC++;
}

/*A function to add to the memory a add command with a register as its source parameter and a matrix parameter as its destination parameter*/
void addRegisterMatrixCmd(parms data)
{
	commandBitField newAddCommand;
	registersParam sourceRegisterParam;
	symbolParam DesinationMatrixParam;
	registersParam DestinationMatrixRegisterParam;

	newAddCommand.fullCommandInt = 0;
	newAddCommand.cBitField.sourceOperandAddressing = Absolute;
	newAddCommand.cBitField.encodingType = DirectRegister;
	newAddCommand.cBitField.destinationOperandAddressing = MatrixAccess;
	newAddCommand.cBitField.opcode = opcodesArray[1].opcodeNum;

	cpuFullMemory[IC].fullReg = newAddCommand.fullCommandInt;
	IC++;

	sourceRegisterParam.fullRegParam = 0;
	sourceRegisterParam.regParam.encodingType = Absolute;
	sourceRegisterParam.regParam.regSource = data.eRegSource;

	cpuFullMemory[IC].fullReg = sourceRegisterParam.fullRegParam;
	IC++;

	DesinationMatrixParam.fullSymbolParam = 0;
	if(data.matrixDestination->external)
	{
		DesinationMatrixParam.symParam.encodingType = External;
		addToExternFile(data.matrixDestination);
	}
	else
		DesinationMatrixParam.symParam.encodingType = Relocatable;
	DesinationMatrixParam.symParam.addressValue = data.matrixDestination->address;

	cpuFullMemory[IC].fullReg = DesinationMatrixParam.fullSymbolParam;
	IC++;

	DestinationMatrixRegisterParam.fullRegParam = 0;
	DestinationMatrixRegisterParam.regParam.encodingType = Absolute;
	DestinationMatrixRegisterParam.regParam.regSource = data.eMatrixRegRowDestination;
	DestinationMatrixRegisterParam.regParam.regDestination = data.eMatrixRegColumnDestination;

	cpuFullMemory[IC].fullReg = DestinationMatrixRegisterParam.fullRegParam;
	IC++;
}

/*A function to add to the memory a add command with a matrix paramater as its source parameter and a register as its destination parameter*/
void addMatrixRegisterCmd(parms data)
{
	commandBitField newAddCommand;
	symbolParam SourceMatrixParam;
	registersParam SourceMatrixRegisterParam;
	registersParam destinationRegisterParam;

	newAddCommand.fullCommandInt = 0;
	newAddCommand.cBitField.encodingType = Absolute;
	newAddCommand.cBitField.sourceOperandAddressing = MatrixAccess;
	newAddCommand.cBitField.destinationOperandAddressing = DirectRegister;
	newAddCommand.cBitField.opcode = opcodesArray[0].opcodeNum;

	cpuFullMemory[IC].fullReg = newAddCommand.fullCommandInt;
	IC++;

	SourceMatrixParam.fullSymbolParam = 0;
	if(data.matrixSource->external)
	{
		SourceMatrixParam.symParam.encodingType = External;
		addToExternFile(data.matrixSource);
	}
	else
		SourceMatrixParam.symParam.encodingType = Relocatable;
	SourceMatrixParam.symParam.addressValue = data.matrixSource->address;

	cpuFullMemory[IC].fullReg = SourceMatrixParam.fullSymbolParam;
	IC++;

	SourceMatrixRegisterParam.fullRegParam = 0;
	SourceMatrixRegisterParam.regParam.encodingType = Absolute;
	SourceMatrixRegisterParam.regParam.regSource = data.eMatrixRegRowSource;
	SourceMatrixRegisterParam.regParam.regDestination = data.eMatrixRegColumnSource;

	cpuFullMemory[IC].fullReg = SourceMatrixRegisterParam.fullRegParam;
	IC++;
	
	destinationRegisterParam.fullRegParam = 0;
	destinationRegisterParam.regParam.encodingType = Absolute;
	destinationRegisterParam.regParam.regDestination = data.eRegDestination;

	cpuFullMemory[IC].fullReg = destinationRegisterParam.fullRegParam;
	IC++;
}

/*A function to add to the memory a add command with a symbol paramater as its source parameter and a register as its destination parameter*/
void addSymbolRegisterCmd(parms data)
{
	commandBitField newAddCommand;
	symbolParam sourceSymbolParam;
	registersParam destinationRegisterParam;

	newAddCommand.fullCommandInt = 0;
	newAddCommand.cBitField.encodingType = Absolute;
	newAddCommand.cBitField.sourceOperandAddressing = Direct;
	newAddCommand.cBitField.destinationOperandAddressing = DirectRegister;
	newAddCommand.cBitField.opcode = opcodesArray[0].opcodeNum;

	cpuFullMemory[IC].fullReg = newAddCommand.fullCommandInt;
	IC++;

	sourceSymbolParam.fullSymbolParam = 0;
	if(data.symbolSource->external)
	{
		sourceSymbolParam.symParam.encodingType = External;
		addToExternFile(data.symbolSource);
	}
	else
		sourceSymbolParam.symParam.encodingType = Relocatable;
	sourceSymbolParam.symParam.addressValue = data.symbolSource->address;

	cpuFullMemory[IC].fullReg = sourceSymbolParam.fullSymbolParam;
	IC++;
	
	destinationRegisterParam.fullRegParam = 0;
	destinationRegisterParam.regParam.encodingType = Absolute;
	destinationRegisterParam.regParam.regDestination = data.eRegDestination;

	cpuFullMemory[IC].fullReg = destinationRegisterParam.fullRegParam;
	IC++;
}

/*A function to add to the memory a add command with a matrix paramater as its source parameter and a symbol parameter as its destination parameter*/
void addMatrixSymbolCmd(parms data)
{
	commandBitField newAddCommand;
	symbolParam SourceMatrixParam;
	registersParam SourceMatrixRegisterParam;
	symbolParam DesinationSymbolParam;

	newAddCommand.fullCommandInt = 0;
	newAddCommand.cBitField.sourceOperandAddressing = Absolute;
	newAddCommand.cBitField.encodingType = MatrixAccess;
	newAddCommand.cBitField.destinationOperandAddressing = Direct;
	newAddCommand.cBitField.opcode = opcodesArray[1].opcodeNum;

	cpuFullMemory[IC].fullReg = newAddCommand.fullCommandInt;
	IC++;

	SourceMatrixParam.fullSymbolParam = 0;
	if(data.matrixSource->external)
	{
		SourceMatrixParam.symParam.encodingType = External;
		addToExternFile(data.matrixSource);
	}
	else
		SourceMatrixParam.symParam.encodingType = Relocatable;
	SourceMatrixParam.symParam.addressValue = data.matrixSource->address;

	cpuFullMemory[IC].fullReg = SourceMatrixParam.fullSymbolParam;
	IC++;

	SourceMatrixRegisterParam.fullRegParam = 0;
	SourceMatrixRegisterParam.regParam.encodingType = Absolute;
	SourceMatrixRegisterParam.regParam.regSource = data.eMatrixRegRowSource;
	SourceMatrixRegisterParam.regParam.regDestination = data.eMatrixRegColumnSource;

	cpuFullMemory[IC].fullReg = SourceMatrixRegisterParam.fullRegParam;
	IC++;
	
	DesinationSymbolParam.fullSymbolParam = 0;
	if(data.symbolDestination->external)
	{
		DesinationSymbolParam.symParam.encodingType = External;
		addToExternFile(data.symbolDestination);
	}
	else
		DesinationSymbolParam.symParam.encodingType = Relocatable;
	DesinationSymbolParam.symParam.addressValue = data.symbolDestination->address;

	cpuFullMemory[IC].fullReg = DesinationSymbolParam.fullSymbolParam;
	IC++;
}

/*A function to add to the memory a add command with a symbol paramater as its source parameter and a symbol parameter as its destination parameter*/
void addSymbolSymbolCmd(parms data)
{
	commandBitField newAddCommand;
	symbolParam SourceSymbolParam;
	symbolParam DesinationSymbolParam;

	newAddCommand.fullCommandInt = 0;
	newAddCommand.cBitField.sourceOperandAddressing = Absolute;
	newAddCommand.cBitField.encodingType = Direct;
	newAddCommand.cBitField.destinationOperandAddressing = Direct;
	newAddCommand.cBitField.opcode = opcodesArray[1].opcodeNum;

	cpuFullMemory[IC].fullReg = newAddCommand.fullCommandInt;
	IC++;

	SourceSymbolParam.fullSymbolParam = 0;
	if(data.symbolSource->external)
	{
		SourceSymbolParam.symParam.encodingType = External;
		addToExternFile(data.symbolSource);
	}
	else
		SourceSymbolParam.symParam.encodingType = Relocatable;
	SourceSymbolParam.symParam.addressValue = data.symbolSource->address;

	cpuFullMemory[IC].fullReg = SourceSymbolParam.fullSymbolParam;
	IC++;
	
	DesinationSymbolParam.fullSymbolParam = 0;
	if(data.symbolDestination->external)
	{
		DesinationSymbolParam.symParam.encodingType = External;
		addToExternFile(data.symbolDestination);
	}
	else
		DesinationSymbolParam.symParam.encodingType = Relocatable;
	DesinationSymbolParam.symParam.addressValue = data.symbolDestination->address;

	cpuFullMemory[IC].fullReg = DesinationSymbolParam.fullSymbolParam;
	IC++;
}

/*A function to add to the memory a add command with a symbol paramater as its source parameter and a matrix parameter as its destination parameter*/
void addSymbolMatrixCmd(parms data)
{
	commandBitField newAddCommand;
	symbolParam SourceSymbolParam;
	symbolParam DesinationMatrixParam;
	registersParam DestinationMatrixRegisterParam;

	newAddCommand.fullCommandInt = 0;
	newAddCommand.cBitField.sourceOperandAddressing = Absolute;
	newAddCommand.cBitField.encodingType = Direct;
	newAddCommand.cBitField.destinationOperandAddressing = MatrixAccess;
	newAddCommand.cBitField.opcode = opcodesArray[1].opcodeNum;

	cpuFullMemory[IC].fullReg = newAddCommand.fullCommandInt;
	IC++;

	SourceSymbolParam.fullSymbolParam = 0;
	if(data.symbolSource->external)
	{
		SourceSymbolParam.symParam.encodingType = External;
		addToExternFile(data.symbolSource);
	}
	else
		SourceSymbolParam.symParam.encodingType = Relocatable;
	SourceSymbolParam.symParam.addressValue = data.symbolSource->address;

	cpuFullMemory[IC].fullReg = SourceSymbolParam.fullSymbolParam;
	IC++;
	
	DesinationMatrixParam.fullSymbolParam = 0;
	if(data.matrixDestination->external)
	{
		DesinationMatrixParam.symParam.encodingType = External;
		addToExternFile(data.matrixDestination);
	}
	else
		DesinationMatrixParam.symParam.encodingType = Relocatable;
	DesinationMatrixParam.symParam.addressValue = data.matrixDestination->address;

	cpuFullMemory[IC].fullReg = DesinationMatrixParam.fullSymbolParam;
	IC++;

	DestinationMatrixRegisterParam.fullRegParam = 0;
	DestinationMatrixRegisterParam.regParam.encodingType = Absolute;
	DestinationMatrixRegisterParam.regParam.regSource = data.eMatrixRegRowDestination;
	DestinationMatrixRegisterParam.regParam.regDestination = data.eMatrixRegColumnDestination;

	cpuFullMemory[IC].fullReg = DestinationMatrixRegisterParam.fullRegParam;
	IC++;
}

/*A function to add to the memory a add command with a matrix paramater as its source parameter and a matrix parameter as its destination parameter*/
void addMatrixMatrixCmd(parms data)
{
	commandBitField newAddCommand;
	symbolParam SourceMatrixParam;
	registersParam SourceMatrixRegisterParam;
	symbolParam DesinationMatrixParam;
	registersParam DestinationMatrixRegisterParam;

	newAddCommand.fullCommandInt = 0;
	newAddCommand.cBitField.sourceOperandAddressing = Absolute;
	newAddCommand.cBitField.encodingType = MatrixAccess;
	newAddCommand.cBitField.destinationOperandAddressing = MatrixAccess;
	newAddCommand.cBitField.opcode = opcodesArray[1].opcodeNum;

	cpuFullMemory[IC].fullReg = newAddCommand.fullCommandInt;
	IC++;

	SourceMatrixParam.fullSymbolParam = 0;
	if(data.matrixSource->external)
	{
		SourceMatrixParam.symParam.encodingType = External;
		addToExternFile(data.matrixSource);
	}
	else
		SourceMatrixParam.symParam.encodingType = Relocatable;
	SourceMatrixParam.symParam.addressValue = data.matrixSource->address;

	cpuFullMemory[IC].fullReg = SourceMatrixParam.fullSymbolParam;
	IC++;

	SourceMatrixRegisterParam.fullRegParam = 0;
	SourceMatrixRegisterParam.regParam.encodingType = Absolute;
	SourceMatrixRegisterParam.regParam.regSource = data.eMatrixRegRowSource;
	SourceMatrixRegisterParam.regParam.regDestination = data.eMatrixRegColumnSource;

	cpuFullMemory[IC].fullReg = SourceMatrixRegisterParam.fullRegParam;
	IC++;
	
	DesinationMatrixParam.fullSymbolParam = 0;
	if(data.matrixDestination->external)
	{
		DesinationMatrixParam.symParam.encodingType = External;
		addToExternFile(data.matrixDestination);
	}
	else
		DesinationMatrixParam.symParam.encodingType = Relocatable;
	DesinationMatrixParam.symParam.addressValue = data.matrixDestination->address;

	cpuFullMemory[IC].fullReg = DesinationMatrixParam.fullSymbolParam;
	IC++;

	DestinationMatrixRegisterParam.fullRegParam = 0;
	DestinationMatrixRegisterParam.regParam.encodingType = Absolute;
	DestinationMatrixRegisterParam.regParam.regSource = data.eMatrixRegRowDestination;
	DestinationMatrixRegisterParam.regParam.regDestination = data.eMatrixRegColumnDestination;

	cpuFullMemory[IC].fullReg = DestinationMatrixRegisterParam.fullRegParam;
	IC++;
}

/*A function to add to the memory a add command with a numeric value as its source parameter and a register as its destination parameter*/
void addValueRegisterCmd(parms data)
{
	commandBitField newAddCommand;
	valueParam sourceValueParam;
	registersParam destinationRegistersParam;

	newAddCommand.fullCommandInt = 0;
	newAddCommand.cBitField.encodingType = Absolute;
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
	destinationRegistersParam.regParam.encodingType = Absolute;
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
	newAddCommand.cBitField.encodingType = Absolute;
	newAddCommand.cBitField.sourceOperandAddressing = Immediate;
	newAddCommand.cBitField.destinationOperandAddressing = Direct;
	newAddCommand.cBitField.opcode = opcodesArray[1].opcodeNum;

	cpuFullMemory[IC].fullReg = newAddCommand.fullCommandInt;
	IC++;

	sourceValueParam.fullValueParam = 0;
	sourceValueParam.valParam.encodingType = Absolute;
	sourceValueParam.valParam.numericValue = data.sourceNum;

	cpuFullMemory[IC].fullReg = sourceValueParam.fullValueParam;
	IC++;
	
	DesinationSymbolParam.fullSymbolParam = 0;
	if(data.symbolDestination->external)
	{
		DesinationSymbolParam.symParam.encodingType = External;
		addToExternFile(data.symbolDestination);
	}
	else
		DesinationSymbolParam.symParam.encodingType = Relocatable;
	DesinationSymbolParam.symParam.addressValue = data.symbolDestination->address;

	cpuFullMemory[IC].fullReg = DesinationSymbolParam.fullSymbolParam;
	IC++;
}

/*A function to add to the memory a add command with a numeric value as its source parameter and a matrix parameter as its destination parameter*/
void addValueMatrixCmd(parms data)
{
	commandBitField newAddCommand;
	valueParam sourceValueParam;
	symbolParam DesinationMatrixParam;
	registersParam DestinationMatrixRegisterParam;

	newAddCommand.fullCommandInt = 0;
	newAddCommand.cBitField.encodingType = Absolute;
	newAddCommand.cBitField.sourceOperandAddressing = Immediate;
	newAddCommand.cBitField.destinationOperandAddressing = MatrixAccess;
	newAddCommand.cBitField.opcode = opcodesArray[1].opcodeNum;

	cpuFullMemory[IC].fullReg = newAddCommand.fullCommandInt;
	IC++;

	sourceValueParam.fullValueParam = 0;
	sourceValueParam.valParam.encodingType = Absolute;
	sourceValueParam.valParam.numericValue = data.sourceNum;

	cpuFullMemory[IC].fullReg = sourceValueParam.fullValueParam;
	IC++;
	
	DesinationMatrixParam.fullSymbolParam = 0;
	if(data.matrixDestination->external)
	{
		DesinationMatrixParam.symParam.encodingType = External;
		addToExternFile(data.matrixDestination);
	}
	else
		DesinationMatrixParam.symParam.encodingType = Relocatable;
	DesinationMatrixParam.symParam.addressValue = data.matrixDestination->address;

	cpuFullMemory[IC].fullReg = DesinationMatrixParam.fullSymbolParam;
	IC++;

	DestinationMatrixRegisterParam.fullRegParam = 0;
	DestinationMatrixRegisterParam.regParam.encodingType = Absolute;
	DestinationMatrixRegisterParam.regParam.regSource = data.eMatrixRegRowDestination;
	DestinationMatrixRegisterParam.regParam.regDestination = data.eMatrixRegColumnDestination;

	cpuFullMemory[IC].fullReg = DestinationMatrixRegisterParam.fullRegParam;
	IC++;
}

/*A function to add to the memory a sub command with a register as its source parameter and a register as its destination parameter*/
void subTwoRegisterCmd(parms data)
{
	commandBitField newSubCommand;
	registersParam srcDstRegistersParam;

	newSubCommand.fullCommandInt = 0;
	newSubCommand.cBitField.encodingType = Absolute;
	newSubCommand.cBitField.sourceOperandAddressing = DirectRegister;
	newSubCommand.cBitField.destinationOperandAddressing = DirectRegister;
	newSubCommand.cBitField.opcode = opcodesArray[3].opcodeNum;

	cpuFullMemory[IC].fullReg = newSubCommand.fullCommandInt;
	IC++;

	srcDstRegistersParam.fullRegParam = 0;
	srcDstRegistersParam.regParam.encodingType = Absolute;
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
	newSubCommand.cBitField.encodingType = Absolute;
	newSubCommand.cBitField.sourceOperandAddressing = DirectRegister;
	newSubCommand.cBitField.destinationOperandAddressing = Direct;
	newSubCommand.cBitField.opcode = opcodesArray[0].opcodeNum;

	cpuFullMemory[IC].fullReg = newSubCommand.fullCommandInt;
	IC++;

	sourceRegisterParam.fullRegParam = 0;
	sourceRegisterParam.regParam.encodingType = Absolute;
	sourceRegisterParam.regParam.regSource = data.eRegSource;

	cpuFullMemory[IC].fullReg = sourceRegisterParam.fullRegParam;
	IC++;

	destinationSymbolParam.fullSymbolParam = 0;
	if(data.symbolDestination->external)
	{
		destinationSymbolParam.symParam.encodingType = External;
		addToExternFile(data.symbolDestination);
	}
	else
		destinationSymbolParam.symParam.encodingType = Relocatable;
	destinationSymbolParam.symParam.addressValue = data.symbolDestination->address;

	cpuFullMemory[IC].fullReg = destinationSymbolParam.fullSymbolParam;
	IC++;
}

/*A function to add to the memory a sub command with a register as its source parameter and a matrix parameter as its destination parameter*/
void subRegisterMatrixCmd(parms data)
{
	commandBitField newSubCommand;
	registersParam sourceRegisterParam;
	symbolParam DesinationMatrixParam;
	registersParam DestinationMatrixRegisterParam;

	newSubCommand.fullCommandInt = 0;
	newSubCommand.cBitField.encodingType = Absolute;
	newSubCommand.cBitField.sourceOperandAddressing = DirectRegister;
	newSubCommand.cBitField.destinationOperandAddressing = MatrixAccess;
	newSubCommand.cBitField.opcode = opcodesArray[0].opcodeNum;

	cpuFullMemory[IC].fullReg = newSubCommand.fullCommandInt;
	IC++;

	sourceRegisterParam.fullRegParam = 0;
	sourceRegisterParam.regParam.encodingType = Absolute;
	sourceRegisterParam.regParam.regSource = data.eRegSource;

	cpuFullMemory[IC].fullReg = sourceRegisterParam.fullRegParam;
	IC++;

	DesinationMatrixParam.fullSymbolParam = 0;
	if(data.matrixDestination->external)
	{
		DesinationMatrixParam.symParam.encodingType = External;
		addToExternFile(data.matrixDestination);
	}
	else
		DesinationMatrixParam.symParam.encodingType = Relocatable;
	DesinationMatrixParam.symParam.addressValue = data.matrixDestination->address;

	cpuFullMemory[IC].fullReg = DesinationMatrixParam.fullSymbolParam;
	IC++;

	DestinationMatrixRegisterParam.fullRegParam = 0;
	DestinationMatrixRegisterParam.regParam.encodingType = Absolute;
	DestinationMatrixRegisterParam.regParam.regSource = data.eMatrixRegRowDestination;
	DestinationMatrixRegisterParam.regParam.regDestination = data.eMatrixRegColumnDestination;

	cpuFullMemory[IC].fullReg = DestinationMatrixRegisterParam.fullRegParam;
	IC++;
}

/*A function to add to the memory a sub command with a symbol paramater as its source parameter and a register as its destination parameter*/
void subSymbolRegisterCmd(parms data)
{
	commandBitField newSubCommand;
	symbolParam sourceSymbolParam;
	registersParam destinationRegisterParam;

	newSubCommand.fullCommandInt = 0;
	newSubCommand.cBitField.encodingType = Absolute;
	newSubCommand.cBitField.sourceOperandAddressing = Direct;
	newSubCommand.cBitField.destinationOperandAddressing = DirectRegister;
	newSubCommand.cBitField.opcode = opcodesArray[0].opcodeNum;

	cpuFullMemory[IC].fullReg = newSubCommand.fullCommandInt;
	IC++;

	sourceSymbolParam.fullSymbolParam = 0;
	if(data.symbolSource->external)
	{
		addToExternFile(data.symbolSource);
		sourceSymbolParam.symParam.encodingType = External;
	}
	else
		sourceSymbolParam.symParam.encodingType = Relocatable;
	sourceSymbolParam.symParam.addressValue = data.symbolSource->address;

	cpuFullMemory[IC].fullReg = sourceSymbolParam.fullSymbolParam;
	IC++;
	
	destinationRegisterParam.fullRegParam = 0;
	destinationRegisterParam.regParam.encodingType = Absolute;
	destinationRegisterParam.regParam.regDestination = data.eRegDestination;

	cpuFullMemory[IC].fullReg = destinationRegisterParam.fullRegParam;
	IC++;
}

/*A function to add to the memory a sub command with a matrix paramater as its source parameter and a register as its destination parameter*/
void subMatrixRegisterCmd(parms data)
{
	commandBitField newSubCommand;
	symbolParam SourceMatrixParam;
	registersParam SourceMatrixRegisterParam;
	registersParam destinationRegisterParam;

	newSubCommand.fullCommandInt = 0;
	newSubCommand.cBitField.encodingType = Absolute;
	newSubCommand.cBitField.sourceOperandAddressing = MatrixAccess;
	newSubCommand.cBitField.destinationOperandAddressing = DirectRegister;
	newSubCommand.cBitField.opcode = opcodesArray[0].opcodeNum;

	cpuFullMemory[IC].fullReg = newSubCommand.fullCommandInt;
	IC++;

	SourceMatrixParam.fullSymbolParam = 0;
	if(data.matrixSource->external)
	{
		SourceMatrixParam.symParam.encodingType = External;
		addToExternFile(data.matrixSource);
	}
	else
		SourceMatrixParam.symParam.encodingType = Relocatable;
	SourceMatrixParam.symParam.addressValue = data.matrixSource->address;

	cpuFullMemory[IC].fullReg = SourceMatrixParam.fullSymbolParam;
	IC++;

	SourceMatrixRegisterParam.fullRegParam = 0;
	SourceMatrixRegisterParam.regParam.encodingType = Absolute;
	SourceMatrixRegisterParam.regParam.regSource = data.eMatrixRegRowSource;
	SourceMatrixRegisterParam.regParam.regDestination = data.eMatrixRegColumnSource;

	cpuFullMemory[IC].fullReg = SourceMatrixRegisterParam.fullRegParam;
	IC++;
	
	destinationRegisterParam.fullRegParam = 0;
	destinationRegisterParam.regParam.encodingType = Absolute;
	destinationRegisterParam.regParam.regDestination = data.eRegDestination;

	cpuFullMemory[IC].fullReg = destinationRegisterParam.fullRegParam;
	IC++;
}

/*A function to add to the memory a sub command with a matrix paramater as its source parameter and a matrix parameter as its destination parameter*/
void subMatrixMatrixCmd(parms data)
{
	commandBitField newSubCommand;
	symbolParam SourceMatrixParam;
	registersParam SourceMatrixRegisterParam;
	symbolParam DesinationMatrixParam;
	registersParam DestinationMatrixRegisterParam;

	newSubCommand.fullCommandInt = 0;
	newSubCommand.cBitField.encodingType = Absolute;
	newSubCommand.cBitField.sourceOperandAddressing = MatrixAccess;
	newSubCommand.cBitField.destinationOperandAddressing = MatrixAccess;
	newSubCommand.cBitField.opcode = opcodesArray[1].opcodeNum;

	cpuFullMemory[IC].fullReg = newSubCommand.fullCommandInt;
	IC++;

	SourceMatrixParam.fullSymbolParam = 0;
	if(data.matrixSource->external)
	{
		SourceMatrixParam.symParam.encodingType = External;
		addToExternFile(data.matrixSource);
	}
	else
		SourceMatrixParam.symParam.encodingType = Relocatable;
	SourceMatrixParam.symParam.addressValue = data.matrixSource->address;

	cpuFullMemory[IC].fullReg = SourceMatrixParam.fullSymbolParam;
	IC++;

	SourceMatrixRegisterParam.fullRegParam = 0;
	SourceMatrixRegisterParam.regParam.encodingType = Absolute;
	SourceMatrixRegisterParam.regParam.regSource = data.eMatrixRegRowSource;
	SourceMatrixRegisterParam.regParam.regDestination = data.eMatrixRegColumnSource;

	cpuFullMemory[IC].fullReg = SourceMatrixRegisterParam.fullRegParam;
	IC++;
	
	DesinationMatrixParam.fullSymbolParam = 0;
	if(data.matrixDestination->external)
	{
		DesinationMatrixParam.symParam.encodingType = External;
		addToExternFile(data.matrixDestination);
	}
	else
		DesinationMatrixParam.symParam.encodingType = Relocatable;
	DesinationMatrixParam.symParam.addressValue = data.matrixDestination->address;

	cpuFullMemory[IC].fullReg = DesinationMatrixParam.fullSymbolParam;
	IC++;

	DestinationMatrixRegisterParam.fullRegParam = 0;
	DestinationMatrixRegisterParam.regParam.encodingType = Absolute;
	DestinationMatrixRegisterParam.regParam.regSource = data.eMatrixRegRowDestination;
	DestinationMatrixRegisterParam.regParam.regDestination = data.eMatrixRegColumnDestination;

	cpuFullMemory[IC].fullReg = DestinationMatrixRegisterParam.fullRegParam;
	IC++;
}

/*A function to add to the memory a sub command with a symbol paramater as its source parameter and a symbol parameter as its destination parameter*/
void subSymbolSymbolCmd(parms data)
{
	commandBitField newSubCommand;
	symbolParam SourceSymbolParam;
	symbolParam DesinationSymbolParam;

	newSubCommand.fullCommandInt = 0;
	newSubCommand.cBitField.encodingType = Absolute;
	newSubCommand.cBitField.sourceOperandAddressing = Direct;
	newSubCommand.cBitField.destinationOperandAddressing = Direct;
	newSubCommand.cBitField.opcode = opcodesArray[1].opcodeNum;

	cpuFullMemory[IC].fullReg = newSubCommand.fullCommandInt;
	IC++;

	SourceSymbolParam.fullSymbolParam = 0;
	if(data.symbolSource->external)
	{
		SourceSymbolParam.symParam.encodingType = External;
		addToExternFile(data.symbolSource);
	}
	else
		SourceSymbolParam.symParam.encodingType = Relocatable;
	SourceSymbolParam.symParam.addressValue = data.symbolSource->address;

	cpuFullMemory[IC].fullReg = SourceSymbolParam.fullSymbolParam;
	IC++;
	
	DesinationSymbolParam.fullSymbolParam = 0;
	if(data.symbolDestination->external)
	{
		DesinationSymbolParam.symParam.encodingType = External;
		addToExternFile(data.symbolDestination);
	}
	else
		DesinationSymbolParam.symParam.encodingType = Relocatable;
	DesinationSymbolParam.symParam.addressValue = data.symbolDestination->address;

	cpuFullMemory[IC].fullReg = DesinationSymbolParam.fullSymbolParam;
	IC++;
}

/*A function to add to the memory a sub command with a matrix paramater as its source parameter and a symbol parameter as its destination parameter*/
void subMatrixSymbolCmd(parms data)
{
	commandBitField newSubCommand;
	symbolParam SourceMatrixParam;
	registersParam SourceMatrixRegisterParam;
	symbolParam DesinationSymbolParam;

	newSubCommand.fullCommandInt = 0;
	newSubCommand.cBitField.encodingType = Absolute;
	newSubCommand.cBitField.sourceOperandAddressing = MatrixAccess;
	newSubCommand.cBitField.destinationOperandAddressing = Direct;
	newSubCommand.cBitField.opcode = opcodesArray[1].opcodeNum;

	cpuFullMemory[IC].fullReg = newSubCommand.fullCommandInt;
	IC++;

	SourceMatrixParam.fullSymbolParam = 0;
	if(data.matrixSource->external)
	{
		SourceMatrixParam.symParam.encodingType = External;
		addToExternFile(data.matrixSource);
	}
	else
		SourceMatrixParam.symParam.encodingType = Relocatable;
	SourceMatrixParam.symParam.addressValue = data.matrixSource->address;

	cpuFullMemory[IC].fullReg = SourceMatrixParam.fullSymbolParam;
	IC++;

	SourceMatrixRegisterParam.fullRegParam = 0;
	SourceMatrixRegisterParam.regParam.encodingType = Absolute;
	SourceMatrixRegisterParam.regParam.regSource = data.eMatrixRegRowSource;
	SourceMatrixRegisterParam.regParam.regDestination = data.eMatrixRegColumnSource;

	cpuFullMemory[IC].fullReg = SourceMatrixRegisterParam.fullRegParam;
	IC++;
	
	DesinationSymbolParam.fullSymbolParam = 0;
	if(data.symbolDestination->external)
	{
		DesinationSymbolParam.symParam.encodingType = External;
		addToExternFile(data.symbolDestination);
	}
	else
		DesinationSymbolParam.symParam.encodingType = Relocatable;
	DesinationSymbolParam.symParam.addressValue = data.symbolDestination->address;

	cpuFullMemory[IC].fullReg = DesinationSymbolParam.fullSymbolParam;
	IC++;
}

/*A function to add to the memory a sub command with a symbol paramater as its source parameter and a matrix parameter as its destination parameter*/
void subSymbolMatrixCmd(parms data)
{
	commandBitField newSubCommand;
	symbolParam SourceSymbolParam;
	symbolParam DesinationMatrixParam;
	registersParam DestinationMatrixRegisterParam;

	newSubCommand.fullCommandInt = 0;
	newSubCommand.cBitField.encodingType = Absolute;
	newSubCommand.cBitField.sourceOperandAddressing = Direct;
	newSubCommand.cBitField.destinationOperandAddressing = MatrixAccess;
	newSubCommand.cBitField.opcode = opcodesArray[1].opcodeNum;

	cpuFullMemory[IC].fullReg = newSubCommand.fullCommandInt;
	IC++;

	SourceSymbolParam.fullSymbolParam = 0;
	if(data.symbolSource->external)
	{
		SourceSymbolParam.symParam.encodingType = External;
		addToExternFile(data.symbolSource);
	}
	else
		SourceSymbolParam.symParam.encodingType = Relocatable;
	SourceSymbolParam.symParam.addressValue = data.symbolSource->address;

	cpuFullMemory[IC].fullReg = SourceSymbolParam.fullSymbolParam;
	IC++;
	
	DesinationMatrixParam.fullSymbolParam = 0;
	if(data.matrixDestination->external)
	{
		DesinationMatrixParam.symParam.encodingType = External;
		addToExternFile(data.matrixDestination);
	}
	else
		DesinationMatrixParam.symParam.encodingType = Relocatable;
	DesinationMatrixParam.symParam.addressValue = data.matrixDestination->address;

	cpuFullMemory[IC].fullReg = DesinationMatrixParam.fullSymbolParam;
	IC++;

	DestinationMatrixRegisterParam.fullRegParam = 0;
	DestinationMatrixRegisterParam.regParam.encodingType = Absolute;
	DestinationMatrixRegisterParam.regParam.regSource = data.eMatrixRegRowDestination;
	DestinationMatrixRegisterParam.regParam.regDestination = data.eMatrixRegColumnDestination;

	cpuFullMemory[IC].fullReg = DestinationMatrixRegisterParam.fullRegParam;
	IC++;
}

/*A function to add to the memory a sub command with a numeric value as its source parameter and a register as its destination parameter*/
void subValueRegisterCmd(parms data)
{
	commandBitField newSubCommand;
	valueParam sourceValueParam;
	registersParam destinationRegistersParam;
	

	newSubCommand.fullCommandInt = 0;
	newSubCommand.cBitField.encodingType = Absolute;
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
	destinationRegistersParam.regParam.encodingType = Absolute;
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
	newSubCommand.cBitField.encodingType = Absolute;
	newSubCommand.cBitField.sourceOperandAddressing = Immediate;
	newSubCommand.cBitField.destinationOperandAddressing = Direct;
	newSubCommand.cBitField.opcode = opcodesArray[1].opcodeNum;

	cpuFullMemory[IC].fullReg = newSubCommand.fullCommandInt;
	IC++;

	sourceValueParam.fullValueParam = 0;
	sourceValueParam.valParam.encodingType = Absolute;
	sourceValueParam.valParam.numericValue = data.sourceNum;

	cpuFullMemory[IC].fullReg = sourceValueParam.fullValueParam;
	IC++;
	
	DesinationSymbolParam.fullSymbolParam = 0;
	if(data.symbolDestination->external)
	{
		DesinationSymbolParam.symParam.encodingType = External;
		addToExternFile(data.symbolDestination);
	}
	else
		DesinationSymbolParam.symParam.encodingType = Relocatable;
	DesinationSymbolParam.symParam.addressValue = data.symbolDestination->address;

	cpuFullMemory[IC].fullReg = DesinationSymbolParam.fullSymbolParam;
	IC++;
}

/*A function to add to the memory a sub command with a numeric value as its source parameter and a matrix parameter as its destination parameter*/
void subValueMatrixCmd(parms data)
{
	commandBitField newSubCommand;
	valueParam sourceValueParam;
	symbolParam DesinationMatrixParam;
	registersParam DestinationMatrixRegisterParam;

	newSubCommand.fullCommandInt = 0;
	newSubCommand.cBitField.encodingType = Absolute;
	newSubCommand.cBitField.sourceOperandAddressing = Immediate;
	newSubCommand.cBitField.destinationOperandAddressing = MatrixAccess;
	newSubCommand.cBitField.opcode = opcodesArray[1].opcodeNum;

	cpuFullMemory[IC].fullReg = newSubCommand.fullCommandInt;
	IC++;

	sourceValueParam.fullValueParam = 0;
	sourceValueParam.valParam.encodingType = Absolute;
	sourceValueParam.valParam.numericValue = data.sourceNum;

	cpuFullMemory[IC].fullReg = sourceValueParam.fullValueParam;
	IC++;
	
	DesinationMatrixParam.fullSymbolParam = 0;
	if(data.matrixDestination->external)
	{
		DesinationMatrixParam.symParam.encodingType = External;
		addToExternFile(data.matrixDestination);
	}
	else
		DesinationMatrixParam.symParam.encodingType = Relocatable;
	DesinationMatrixParam.symParam.addressValue = data.matrixDestination->address;

	cpuFullMemory[IC].fullReg = DesinationMatrixParam.fullSymbolParam;
	IC++;

	DestinationMatrixRegisterParam.fullRegParam = 0;
	DestinationMatrixRegisterParam.regParam.encodingType = Absolute;
	DestinationMatrixRegisterParam.regParam.regSource = data.eMatrixRegRowDestination;
	DestinationMatrixRegisterParam.regParam.regDestination = data.eMatrixRegColumnDestination;

	cpuFullMemory[IC].fullReg = DestinationMatrixRegisterParam.fullRegParam;
	IC++;
}

/*A function to add to the memory a lea command with a register as its source parameter and a register as its destination parameter*/
void leaTwoRegisterCmd(parms data)
{
	commandBitField newLeaCommand;
	registersParam srcDstRegistersParam;

	newLeaCommand.fullCommandInt = 0;
	newLeaCommand.cBitField.encodingType = Absolute;
	newLeaCommand.cBitField.sourceOperandAddressing = DirectRegister;
	newLeaCommand.cBitField.destinationOperandAddressing = DirectRegister;
	newLeaCommand.cBitField.opcode = opcodesArray[6].opcodeNum;

	cpuFullMemory[IC].fullReg = newLeaCommand.fullCommandInt;
	IC++;

	srcDstRegistersParam.fullRegParam = 0;
	srcDstRegistersParam.regParam.encodingType = Absolute;
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
	newLeaCommand.cBitField.encodingType = Absolute;
	newLeaCommand.cBitField.sourceOperandAddressing = DirectRegister;
	newLeaCommand.cBitField.destinationOperandAddressing = Direct;
	newLeaCommand.cBitField.opcode = opcodesArray[0].opcodeNum;

	cpuFullMemory[IC].fullReg = newLeaCommand.fullCommandInt;
	IC++;

	sourceRegisterParam.fullRegParam = 0;
	sourceRegisterParam.regParam.encodingType = Absolute;
	sourceRegisterParam.regParam.regSource = data.eRegSource;

	cpuFullMemory[IC].fullReg = sourceRegisterParam.fullRegParam;
	IC++;

	destinationSymbolParam.fullSymbolParam = 0;
	if(data.symbolDestination->external)
	{
		destinationSymbolParam.symParam.encodingType = External;
		addToExternFile(data.symbolDestination);
	}
	else
		destinationSymbolParam.symParam.encodingType = Relocatable;
	destinationSymbolParam.symParam.addressValue = data.symbolDestination->address;

	cpuFullMemory[IC].fullReg = destinationSymbolParam.fullSymbolParam;
	IC++;
}

/*A function to add to the memory a lea command with a matrix parameter as its source parameter and a symbol parameter as its destination parameter*/
void leaMatrixSymbolCmd(parms data)
{
	commandBitField newLeaCommand;
	symbolParam SourceMatrixParam;
	registersParam SourceMatrixRegisterParam;
	symbolParam destinationSymbolParam;

	newLeaCommand.fullCommandInt = 0;
	newLeaCommand.cBitField.encodingType = Absolute;
	newLeaCommand.cBitField.sourceOperandAddressing = MatrixAccess;
	newLeaCommand.cBitField.destinationOperandAddressing = Direct;
	newLeaCommand.cBitField.opcode = opcodesArray[0].opcodeNum;

	cpuFullMemory[IC].fullReg = newLeaCommand.fullCommandInt;
	IC++;

	SourceMatrixParam.fullSymbolParam = 0;
	if(data.matrixSource->external)
	{
		SourceMatrixParam.symParam.encodingType = External;
		addToExternFile(data.matrixSource);
	}
	else
		SourceMatrixParam.symParam.encodingType = Relocatable;
	SourceMatrixParam.symParam.addressValue = data.matrixSource->address;

	cpuFullMemory[IC].fullReg = SourceMatrixParam.fullSymbolParam;
	IC++;

	SourceMatrixRegisterParam.fullRegParam = 0;
	SourceMatrixRegisterParam.regParam.encodingType = Absolute;
	SourceMatrixRegisterParam.regParam.regSource = data.eMatrixRegRowSource;
	SourceMatrixRegisterParam.regParam.regDestination = data.eMatrixRegColumnSource;

	cpuFullMemory[IC].fullReg = SourceMatrixRegisterParam.fullRegParam;
	IC++;

	destinationSymbolParam.fullSymbolParam = 0;
	if(data.symbolDestination->external)
	{
		destinationSymbolParam.symParam.encodingType = External;
		addToExternFile(data.symbolDestination);
	}
	else
		destinationSymbolParam.symParam.encodingType = Relocatable;
	destinationSymbolParam.symParam.addressValue = data.symbolDestination->address;

	cpuFullMemory[IC].fullReg = destinationSymbolParam.fullSymbolParam;
	IC++;
}

/*A function to add to the memory a lea command with a register as its source parameter and a matrix parameter as its destination parameter*/
void leaRegisterMatrixCmd(parms data)
{
	commandBitField newLeaCommand;
	registersParam sourceRegisterParam;
	symbolParam DesinationMatrixParam;
	registersParam DestinationMatrixRegisterParam;

	newLeaCommand.fullCommandInt = 0;
	newLeaCommand.cBitField.encodingType = Absolute;
	newLeaCommand.cBitField.sourceOperandAddressing = DirectRegister;
	newLeaCommand.cBitField.destinationOperandAddressing = MatrixAccess;
	newLeaCommand.cBitField.opcode = opcodesArray[0].opcodeNum;

	cpuFullMemory[IC].fullReg = newLeaCommand.fullCommandInt;
	IC++;

	sourceRegisterParam.fullRegParam = 0;
	sourceRegisterParam.regParam.encodingType = Absolute;
	sourceRegisterParam.regParam.regSource = data.eRegSource;

	cpuFullMemory[IC].fullReg = sourceRegisterParam.fullRegParam;
	IC++;

	DesinationMatrixParam.fullSymbolParam = 0;
	if(data.matrixDestination->external)
	{
		DesinationMatrixParam.symParam.encodingType = External;
		addToExternFile(data.matrixDestination);
	}
	else
		DesinationMatrixParam.symParam.encodingType = Relocatable;
	DesinationMatrixParam.symParam.addressValue = data.matrixDestination->address;

	cpuFullMemory[IC].fullReg = DesinationMatrixParam.fullSymbolParam;
	IC++;

	DestinationMatrixRegisterParam.fullRegParam = 0;
	DestinationMatrixRegisterParam.regParam.encodingType = Absolute;
	DestinationMatrixRegisterParam.regParam.regSource = data.eMatrixRegRowDestination;
	DestinationMatrixRegisterParam.regParam.regDestination = data.eMatrixRegColumnDestination;

	cpuFullMemory[IC].fullReg = DestinationMatrixRegisterParam.fullRegParam;
	IC++;
}

/*A function to add to the memory a lea command with a symbol paramater as its source parameter and a register as its destination parameter*/
void leaSymbolRegisterCmd(parms data)
{
	commandBitField newLeaCommand;
	symbolParam sourceSymbolParam;
	registersParam destinationRegisterParam;

	newLeaCommand.fullCommandInt = 0;
	newLeaCommand.cBitField.encodingType = Absolute;
	newLeaCommand.cBitField.sourceOperandAddressing = Direct;
	newLeaCommand.cBitField.destinationOperandAddressing = DirectRegister;
	newLeaCommand.cBitField.opcode = opcodesArray[0].opcodeNum;

	cpuFullMemory[IC].fullReg = newLeaCommand.fullCommandInt;
	IC++;

	sourceSymbolParam.fullSymbolParam = 0;
	if(data.symbolSource->external)
	{
		sourceSymbolParam.symParam.encodingType = External;
		addToExternFile(data.symbolSource);
	}
	else
		sourceSymbolParam.symParam.encodingType = Relocatable;
	sourceSymbolParam.symParam.addressValue = data.symbolSource->address;

	cpuFullMemory[IC].fullReg = sourceSymbolParam.fullSymbolParam;
	IC++;
	
	destinationRegisterParam.fullRegParam = 0;
	destinationRegisterParam.regParam.encodingType = Absolute;
	destinationRegisterParam.regParam.regDestination = data.eRegDestination;

	cpuFullMemory[IC].fullReg = destinationRegisterParam.fullRegParam;
	IC++;
}

/*A function to add to the memory a lea command with a matrix paramater as its source parameter and a register as its destination parameter*/
void leaMatrixRegisterCmd(parms data)
{
	commandBitField newLeaCommand;
	symbolParam SourceMatrixParam;
	registersParam SourceMatrixRegisterParam;
	registersParam destinationRegisterParam;

	newLeaCommand.fullCommandInt = 0;
	newLeaCommand.cBitField.encodingType = Absolute;
	newLeaCommand.cBitField.sourceOperandAddressing = MatrixAccess;
	newLeaCommand.cBitField.destinationOperandAddressing = DirectRegister;
	newLeaCommand.cBitField.opcode = opcodesArray[0].opcodeNum;

	cpuFullMemory[IC].fullReg = newLeaCommand.fullCommandInt;
	IC++;

	SourceMatrixParam.fullSymbolParam = 0;
	if(data.matrixSource->external)
	{
		SourceMatrixParam.symParam.encodingType = External;
		addToExternFile(data.matrixSource);
	}
	else
		SourceMatrixParam.symParam.encodingType = Relocatable;
	SourceMatrixParam.symParam.addressValue = data.matrixSource->address;

	cpuFullMemory[IC].fullReg = SourceMatrixParam.fullSymbolParam;
	IC++;

	SourceMatrixRegisterParam.fullRegParam = 0;
	SourceMatrixRegisterParam.regParam.encodingType = Absolute;
	SourceMatrixRegisterParam.regParam.regSource = data.eMatrixRegRowSource;
	SourceMatrixRegisterParam.regParam.regDestination = data.eMatrixRegColumnSource;

	cpuFullMemory[IC].fullReg = SourceMatrixRegisterParam.fullRegParam;
	IC++;
	
	destinationRegisterParam.fullRegParam = 0;
	destinationRegisterParam.regParam.encodingType = Absolute;
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
	newLeaCommand.cBitField.encodingType = Absolute;
	newLeaCommand.cBitField.sourceOperandAddressing = Direct;
	newLeaCommand.cBitField.destinationOperandAddressing = Direct;
	newLeaCommand.cBitField.opcode = opcodesArray[1].opcodeNum;

	cpuFullMemory[IC].fullReg = newLeaCommand.fullCommandInt;
	IC++;

	SourceSymbolParam.fullSymbolParam = 0;
	if(data.symbolSource->external)
	{
		SourceSymbolParam.symParam.encodingType = External;
		addToExternFile(data.symbolSource);
	}
	else
		SourceSymbolParam.symParam.encodingType = Relocatable;
	SourceSymbolParam.symParam.addressValue = data.symbolSource->address;

	cpuFullMemory[IC].fullReg = SourceSymbolParam.fullSymbolParam;
	IC++;
	
	DesinationSymbolParam.fullSymbolParam = 0;
	if(data.symbolDestination->external)
	{
		DesinationSymbolParam.symParam.encodingType = External;
		addToExternFile(data.symbolDestination);
	}
	else
		DesinationSymbolParam.symParam.encodingType = Relocatable;
	DesinationSymbolParam.symParam.addressValue = data.symbolDestination->address;

	cpuFullMemory[IC].fullReg = DesinationSymbolParam.fullSymbolParam;
	IC++;
}

/*A function to add to the memory a lea command with a symbol paramater as its source parameter and a matrix parameter as its destination parameter*/
void leaSymbolMatrixCmd(parms data)
{
	commandBitField newLeaCommand;
	symbolParam SourceSymbolParam;
	symbolParam DesinationMatrixParam;
	registersParam DestinationMatrixRegisterParam;

	newLeaCommand.fullCommandInt = 0;
	newLeaCommand.cBitField.encodingType = Absolute;
	newLeaCommand.cBitField.sourceOperandAddressing = Direct;
	newLeaCommand.cBitField.destinationOperandAddressing = MatrixAccess;
	newLeaCommand.cBitField.opcode = opcodesArray[1].opcodeNum;

	cpuFullMemory[IC].fullReg = newLeaCommand.fullCommandInt;
	IC++;

	SourceSymbolParam.fullSymbolParam = 0;
	if(data.symbolSource->external)
	{
		SourceSymbolParam.symParam.encodingType = External;
		addToExternFile(data.symbolSource);
	}
	else
		SourceSymbolParam.symParam.encodingType = Relocatable;
	SourceSymbolParam.symParam.addressValue = data.symbolSource->address;

	cpuFullMemory[IC].fullReg = SourceSymbolParam.fullSymbolParam;
	IC++;
	
	DesinationMatrixParam.fullSymbolParam = 0;
	if(data.matrixDestination->external)
	{
		DesinationMatrixParam.symParam.encodingType = External;
		addToExternFile(data.matrixDestination);
	}
	else
		DesinationMatrixParam.symParam.encodingType = Relocatable;
	DesinationMatrixParam.symParam.addressValue = data.matrixDestination->address;

	cpuFullMemory[IC].fullReg = DesinationMatrixParam.fullSymbolParam;
	IC++;

	DestinationMatrixRegisterParam.fullRegParam = 0;
	DestinationMatrixRegisterParam.regParam.encodingType = Absolute;
	DestinationMatrixRegisterParam.regParam.regSource = data.eMatrixRegRowDestination;
	DestinationMatrixRegisterParam.regParam.regDestination = data.eMatrixRegColumnDestination;

	cpuFullMemory[IC].fullReg = DestinationMatrixRegisterParam.fullRegParam;
	IC++;
}

/*A function to add to the memory a lea command with a matrix paramater as its source parameter and a matrix parameter as its destination parameter*/
void leaMatrixMatrixCmd(parms data)
{
	commandBitField newLeaCommand;
	symbolParam SourceMatrixParam;
	registersParam SourceMatrixRegisterParam;
	symbolParam DesinationMatrixParam;
	registersParam DestinationMatrixRegisterParam;

	newLeaCommand.fullCommandInt = 0;
	newLeaCommand.cBitField.encodingType = Absolute;
	newLeaCommand.cBitField.sourceOperandAddressing = MatrixAccess;
	newLeaCommand.cBitField.destinationOperandAddressing = MatrixAccess;
	newLeaCommand.cBitField.opcode = opcodesArray[1].opcodeNum;

	cpuFullMemory[IC].fullReg = newLeaCommand.fullCommandInt;
	IC++;

	SourceMatrixParam.fullSymbolParam = 0;
	if(data.matrixSource->external)
	{
		SourceMatrixParam.symParam.encodingType = External;
		addToExternFile(data.matrixSource);
	}
	else
		SourceMatrixParam.symParam.encodingType = Relocatable;
	SourceMatrixParam.symParam.addressValue = data.matrixSource->address;

	cpuFullMemory[IC].fullReg = SourceMatrixParam.fullSymbolParam;
	IC++;

	SourceMatrixRegisterParam.fullRegParam = 0;
	SourceMatrixRegisterParam.regParam.encodingType = Absolute;
	SourceMatrixRegisterParam.regParam.regSource = data.eMatrixRegRowSource;
	SourceMatrixRegisterParam.regParam.regDestination = data.eMatrixRegColumnSource;

	cpuFullMemory[IC].fullReg = SourceMatrixRegisterParam.fullRegParam;
	IC++;
	
	DesinationMatrixParam.fullSymbolParam = 0;
	if(data.matrixDestination->external)
	{
		DesinationMatrixParam.symParam.encodingType = External;
		addToExternFile(data.matrixDestination);
	}
	else
		DesinationMatrixParam.symParam.encodingType = Relocatable;
	DesinationMatrixParam.symParam.addressValue = data.matrixDestination->address;

	cpuFullMemory[IC].fullReg = DesinationMatrixParam.fullSymbolParam;
	IC++;

	DestinationMatrixRegisterParam.fullRegParam = 0;
	DestinationMatrixRegisterParam.regParam.encodingType = Absolute;
	DestinationMatrixRegisterParam.regParam.regSource = data.eMatrixRegRowDestination;
	DestinationMatrixRegisterParam.regParam.regDestination = data.eMatrixRegColumnDestination;

	cpuFullMemory[IC].fullReg = DestinationMatrixRegisterParam.fullRegParam;
	IC++;
}

/*A function to add to the memory a lea command with a numeric value as its source parameter and a register as its destination parameter*/
void leaValueRegisterCmd(parms data)
{
	commandBitField newLeaCommand;
	valueParam sourceValueParam;
	registersParam destinationRegistersParam;

	newLeaCommand.fullCommandInt = 0;
	newLeaCommand.cBitField.encodingType = Absolute;
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
	destinationRegistersParam.regParam.encodingType = Absolute;
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
	newLeaCommand.cBitField.encodingType = Absolute;
	newLeaCommand.cBitField.sourceOperandAddressing = Immediate;
	newLeaCommand.cBitField.destinationOperandAddressing = Direct;
	newLeaCommand.cBitField.opcode = opcodesArray[1].opcodeNum;

	cpuFullMemory[IC].fullReg = newLeaCommand.fullCommandInt;
	IC++;

	sourceValueParam.fullValueParam = 0;
	sourceValueParam.valParam.encodingType = Absolute;
	sourceValueParam.valParam.numericValue = data.sourceNum;

	cpuFullMemory[IC].fullReg = sourceValueParam.fullValueParam;
	IC++;
	
	DesinationSymbolParam.fullSymbolParam = 0;
	if(data.symbolDestination->external)
	{
		DesinationSymbolParam.symParam.encodingType = External;
		addToExternFile(data.symbolDestination);
	}
	else
		DesinationSymbolParam.symParam.encodingType = Relocatable;
	DesinationSymbolParam.symParam.addressValue = data.symbolDestination->address;

	cpuFullMemory[IC].fullReg = DesinationSymbolParam.fullSymbolParam;
	IC++;
}

/*A function to add to the memory a lea command with a numeric value as its source parameter and a matrix parameter as its destination parameter*/
void leaValueMatrixCmd(parms data)
{
	commandBitField newLeaCommand;
	valueParam sourceValueParam;
	symbolParam DesinationMatrixParam;
	registersParam DestinationMatrixRegisterParam;

	newLeaCommand.fullCommandInt = 0;
	newLeaCommand.cBitField.encodingType = Absolute;
	newLeaCommand.cBitField.sourceOperandAddressing = Immediate;
	newLeaCommand.cBitField.destinationOperandAddressing = MatrixAccess;
	newLeaCommand.cBitField.opcode = opcodesArray[1].opcodeNum;

	cpuFullMemory[IC].fullReg = newLeaCommand.fullCommandInt;
	IC++;

	sourceValueParam.fullValueParam = 0;
	sourceValueParam.valParam.encodingType = Absolute;
	sourceValueParam.valParam.numericValue = data.sourceNum;

	cpuFullMemory[IC].fullReg = sourceValueParam.fullValueParam;
	IC++;
	
	DesinationMatrixParam.fullSymbolParam = 0;
	if(data.matrixDestination->external)
	{
		DesinationMatrixParam.symParam.encodingType = External;
		addToExternFile(data.matrixDestination);
	}
	else
		DesinationMatrixParam.symParam.encodingType = Relocatable;
	DesinationMatrixParam.symParam.addressValue = data.matrixDestination->address;

	cpuFullMemory[IC].fullReg = DesinationMatrixParam.fullSymbolParam;
	IC++;

	DestinationMatrixRegisterParam.fullRegParam = 0;
	DestinationMatrixRegisterParam.regParam.encodingType = Absolute;
	DestinationMatrixRegisterParam.regParam.regSource = data.eMatrixRegRowDestination;
	DestinationMatrixRegisterParam.regParam.regDestination = data.eMatrixRegColumnDestination;

	cpuFullMemory[IC].fullReg = DestinationMatrixRegisterParam.fullRegParam;
	IC++;
}

/*A function to add to the memory a not command with a register as its destination parameter*/
void notRegisterCmd(parms data)
{
	commandBitField newNotCommand;
	registersParam destinationRegistersParam;

	newNotCommand.fullCommandInt = 0;
	newNotCommand.cBitField.encodingType = Absolute;
	newNotCommand.cBitField.destinationOperandAddressing = DirectRegister;
	newNotCommand.cBitField.opcode = opcodesArray[4].opcodeNum;

	cpuFullMemory[IC].fullReg = newNotCommand.fullCommandInt;
	IC++;

	destinationRegistersParam.fullRegParam = 0;
	destinationRegistersParam.regParam.encodingType = Absolute;
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
	newNotCommand.cBitField.encodingType = Absolute;
	newNotCommand.cBitField.destinationOperandAddressing = Direct;
	newNotCommand.cBitField.opcode = opcodesArray[4].opcodeNum;

	cpuFullMemory[IC].fullReg = newNotCommand.fullCommandInt;
	IC++;

	DesinationSymbolParam.fullSymbolParam = 0;
	if(data.symbolDestination->external)
	{
		DesinationSymbolParam.symParam.encodingType = External;
		addToExternFile(data.symbolDestination);
	}
	else
		DesinationSymbolParam.symParam.encodingType = Relocatable;
	DesinationSymbolParam.symParam.addressValue = data.symbolDestination->address;

	cpuFullMemory[IC].fullReg = DesinationSymbolParam.fullSymbolParam;
	IC++;
}

/*A function to add to the memory a not command with a matrix paramater as its destination parameter*/
void notMatrixCmd(parms data)
{
	commandBitField newNotCommand;
	symbolParam DesinationMatrixParam;
	registersParam DestinationMatrixRegisterParam;

	newNotCommand.fullCommandInt = 0;
	newNotCommand.cBitField.encodingType = Absolute;
	newNotCommand.cBitField.destinationOperandAddressing = MatrixAccess;
	newNotCommand.cBitField.opcode = opcodesArray[4].opcodeNum;

	cpuFullMemory[IC].fullReg = newNotCommand.fullCommandInt;
	IC++;

	DesinationMatrixParam.fullSymbolParam = 0;
	if(data.matrixDestination->external)
	{
		DesinationMatrixParam.symParam.encodingType = External;
		addToExternFile(data.matrixDestination);
	}
	else
		DesinationMatrixParam.symParam.encodingType = Relocatable;
	DesinationMatrixParam.symParam.addressValue = data.matrixDestination->address;

	cpuFullMemory[IC].fullReg = DesinationMatrixParam.fullSymbolParam;
	IC++;

	DestinationMatrixRegisterParam.fullRegParam = 0;
	DestinationMatrixRegisterParam.regParam.encodingType = Absolute;
	DestinationMatrixRegisterParam.regParam.regSource = data.eMatrixRegRowDestination;
	DestinationMatrixRegisterParam.regParam.regDestination = data.eMatrixRegColumnDestination;

	cpuFullMemory[IC].fullReg = DestinationMatrixRegisterParam.fullRegParam;
	IC++;
}

/*A function to add to the memory a clr command with a register as its destination parameter*/
void clrRegisterCmd(parms data)
{
	commandBitField newClrCommand;
	registersParam destinationRegistersParam;

	newClrCommand.fullCommandInt = 0;
	newClrCommand.cBitField.encodingType = Absolute;
	newClrCommand.cBitField.destinationOperandAddressing = DirectRegister;
	newClrCommand.cBitField.opcode = opcodesArray[5].opcodeNum;

	cpuFullMemory[IC].fullReg = newClrCommand.fullCommandInt;
	IC++;

	destinationRegistersParam.fullRegParam = 0;
	destinationRegistersParam.regParam.encodingType = Absolute;
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
	newClrCommand.cBitField.encodingType = Absolute;
	newClrCommand.cBitField.destinationOperandAddressing = Direct;
	newClrCommand.cBitField.opcode = opcodesArray[5].opcodeNum;

	cpuFullMemory[IC].fullReg = newClrCommand.fullCommandInt;
	IC++;

	DesinationSymbolParam.fullSymbolParam = 0;
	if(data.symbolDestination->external)
	{
		DesinationSymbolParam.symParam.encodingType = External;
		addToExternFile(data.symbolDestination);
	}
	else
		DesinationSymbolParam.symParam.encodingType = Relocatable;
	DesinationSymbolParam.symParam.addressValue = data.symbolDestination->address;

	cpuFullMemory[IC].fullReg = DesinationSymbolParam.fullSymbolParam;
	IC++;
}

/*A function to add to the memory a clr command with a matrix paramater as its destination parameter*/
void clrMatrixCmd(parms data)
{
	commandBitField newClrCommand;
	symbolParam DesinationMatrixParam;
	registersParam DestinationMatrixRegisterParam;

	newClrCommand.fullCommandInt = 0;
	newClrCommand.cBitField.encodingType = Absolute;
	newClrCommand.cBitField.destinationOperandAddressing = MatrixAccess;
	newClrCommand.cBitField.opcode = opcodesArray[5].opcodeNum;

	cpuFullMemory[IC].fullReg = newClrCommand.fullCommandInt;
	IC++;

	DesinationMatrixParam.fullSymbolParam = 0;
	if(data.matrixDestination->external)
	{
		DesinationMatrixParam.symParam.encodingType = External;
		addToExternFile(data.matrixDestination);
	}
	else
		DesinationMatrixParam.symParam.encodingType = Relocatable;
	DesinationMatrixParam.symParam.addressValue = data.matrixDestination->address;

	cpuFullMemory[IC].fullReg = DesinationMatrixParam.fullSymbolParam;
	IC++;

	DestinationMatrixRegisterParam.fullRegParam = 0;
	DestinationMatrixRegisterParam.regParam.encodingType = Absolute;
	DestinationMatrixRegisterParam.regParam.regSource = data.eMatrixRegRowDestination;
	DestinationMatrixRegisterParam.regParam.regDestination = data.eMatrixRegColumnDestination;

	cpuFullMemory[IC].fullReg = DestinationMatrixRegisterParam.fullRegParam;
	IC++;
}

/*A function to add to the memory an inc command with a register as its destination parameter*/
void incRegisterCmd(parms data)
{
	commandBitField newIncCommand;
	registersParam destinationRegistersParam;

	newIncCommand.fullCommandInt = 0;
	newIncCommand.cBitField.encodingType = Absolute;
	newIncCommand.cBitField.destinationOperandAddressing = DirectRegister;
	newIncCommand.cBitField.opcode = opcodesArray[7].opcodeNum;

	cpuFullMemory[IC].fullReg = newIncCommand.fullCommandInt;
	IC++;

	destinationRegistersParam.fullRegParam = 0;
	destinationRegistersParam.regParam.encodingType = Absolute;
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
	newIncCommand.cBitField.encodingType = Absolute;
	newIncCommand.cBitField.destinationOperandAddressing = Direct;
	newIncCommand.cBitField.opcode = opcodesArray[7].opcodeNum;

	cpuFullMemory[IC].fullReg = newIncCommand.fullCommandInt;
	IC++;

	DesinationSymbolParam.fullSymbolParam = 0;
	if(data.symbolDestination->external)
	{
		DesinationSymbolParam.symParam.encodingType = External;
		addToExternFile(data.symbolDestination);
	}
	else
		DesinationSymbolParam.symParam.encodingType = Relocatable;
	DesinationSymbolParam.symParam.addressValue = data.symbolDestination->address;

	cpuFullMemory[IC].fullReg = DesinationSymbolParam.fullSymbolParam;
	IC++;
}

/*A function to add to the memory a inc command with a matrix paramater as its destination parameter*/
void incMatrixCmd(parms data)
{
	commandBitField newIncCommand;
	symbolParam DesinationMatrixParam;
	registersParam DestinationMatrixRegisterParam;

	newIncCommand.fullCommandInt = 0;
	newIncCommand.cBitField.encodingType = Absolute;
	newIncCommand.cBitField.destinationOperandAddressing = MatrixAccess;
	newIncCommand.cBitField.opcode = opcodesArray[7].opcodeNum;

	cpuFullMemory[IC].fullReg = newIncCommand.fullCommandInt;
	IC++;

	DesinationMatrixParam.fullSymbolParam = 0;
	if(data.matrixDestination->external)
	{
		DesinationMatrixParam.symParam.encodingType = External;
		addToExternFile(data.matrixDestination);
	}
	else
		DesinationMatrixParam.symParam.encodingType = Relocatable;
	DesinationMatrixParam.symParam.addressValue = data.matrixDestination->address;

	cpuFullMemory[IC].fullReg = DesinationMatrixParam.fullSymbolParam;
	IC++;

	DestinationMatrixRegisterParam.fullRegParam = 0;
	DestinationMatrixRegisterParam.regParam.encodingType = Absolute;
	DestinationMatrixRegisterParam.regParam.regSource = data.eMatrixRegRowDestination;
	DestinationMatrixRegisterParam.regParam.regDestination = data.eMatrixRegColumnDestination;

	cpuFullMemory[IC].fullReg = DestinationMatrixRegisterParam.fullRegParam;
	IC++;
}

/*A function to add to the memory a dec command with a register as its destination parameter*/
void decRegisterCmd(parms data)
{
	commandBitField newDecCommand;
	registersParam destinationRegistersParam;

	newDecCommand.fullCommandInt = 0;
	newDecCommand.cBitField.encodingType = Absolute;
	newDecCommand.cBitField.destinationOperandAddressing = DirectRegister;
	newDecCommand.cBitField.opcode = opcodesArray[8].opcodeNum;

	cpuFullMemory[IC].fullReg = newDecCommand.fullCommandInt;
	IC++;

	destinationRegistersParam.fullRegParam = 0;
	destinationRegistersParam.regParam.encodingType = Absolute;
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
	newDecCommand.cBitField.encodingType = Absolute;
	newDecCommand.cBitField.destinationOperandAddressing = Direct;
	newDecCommand.cBitField.opcode = opcodesArray[7].opcodeNum;

	cpuFullMemory[IC].fullReg = newDecCommand.fullCommandInt;
	IC++;

	DesinationSymbolParam.fullSymbolParam = 0;
	if(data.symbolDestination->external)
	{
		DesinationSymbolParam.symParam.encodingType = External;
		addToExternFile(data.symbolDestination);
	}
	else
		DesinationSymbolParam.symParam.encodingType = Relocatable;
	DesinationSymbolParam.symParam.addressValue = data.symbolDestination->address;

	cpuFullMemory[IC].fullReg = DesinationSymbolParam.fullSymbolParam;
	IC++;
}

/*A function to add to the memory a dec command with a matrix paramater as its destination parameter*/
void decMatrixCmd(parms data)
{
	commandBitField newDecCommand;
	symbolParam DesinationMatrixParam;
	registersParam DestinationMatrixRegisterParam;

	newDecCommand.fullCommandInt = 0;
	newDecCommand.cBitField.encodingType = Absolute;
	newDecCommand.cBitField.destinationOperandAddressing = MatrixAccess;
	newDecCommand.cBitField.opcode = opcodesArray[7].opcodeNum;

	cpuFullMemory[IC].fullReg = newDecCommand.fullCommandInt;
	IC++;

	DesinationMatrixParam.fullSymbolParam = 0;
	if(data.matrixDestination->external)
	{
		DesinationMatrixParam.symParam.encodingType = External;
		addToExternFile(data.matrixDestination);
	}
	else
		DesinationMatrixParam.symParam.encodingType = Relocatable;
	DesinationMatrixParam.symParam.addressValue = data.matrixDestination->address;

	cpuFullMemory[IC].fullReg = DesinationMatrixParam.fullSymbolParam;
	IC++;

	DestinationMatrixRegisterParam.fullRegParam = 0;
	DestinationMatrixRegisterParam.regParam.encodingType = Absolute;
	DestinationMatrixRegisterParam.regParam.regSource = data.eMatrixRegRowDestination;
	DestinationMatrixRegisterParam.regParam.regDestination = data.eMatrixRegColumnDestination;

	cpuFullMemory[IC].fullReg = DestinationMatrixRegisterParam.fullRegParam;
	IC++;
}

/*A function to add to the memory a jmp command with a register as its destination parameter*/
void jmpRegisterCmd(parms data)
{
	commandBitField newJmpCommand;
	registersParam destinationRegistersParam;

	newJmpCommand.fullCommandInt = 0;
	newJmpCommand.cBitField.encodingType = Absolute;
	newJmpCommand.cBitField.destinationOperandAddressing = DirectRegister;
	newJmpCommand.cBitField.opcode = opcodesArray[9].opcodeNum;

	cpuFullMemory[IC].fullReg = newJmpCommand.fullCommandInt;
	IC++;

	destinationRegistersParam.fullRegParam = 0;
	destinationRegistersParam.regParam.encodingType = Absolute;
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
	newJmpCommand.cBitField.encodingType = Absolute;
	newJmpCommand.cBitField.destinationOperandAddressing = Direct;
	newJmpCommand.cBitField.opcode = opcodesArray[7].opcodeNum;

	cpuFullMemory[IC].fullReg = newJmpCommand.fullCommandInt;
	IC++;

	DesinationSymbolParam.fullSymbolParam = 0;
	if(data.symbolDestination->external)
	{
		DesinationSymbolParam.symParam.encodingType = External;
		addToExternFile(data.symbolDestination);
	}
	else
		DesinationSymbolParam.symParam.encodingType = Relocatable;
	DesinationSymbolParam.symParam.addressValue = data.symbolDestination->address;

	cpuFullMemory[IC].fullReg = DesinationSymbolParam.fullSymbolParam;
	IC++;
}

/*A function to add to the memory a jmp command with a matrix paramater as its destination parameter*/
void jmpMatrixCmd(parms data)
{
	commandBitField newJmpCommand;
	symbolParam DesinationMatrixParam;
	registersParam DestinationMatrixRegisterParam;

	newJmpCommand.fullCommandInt = 0;
	newJmpCommand.cBitField.encodingType = Absolute;
	newJmpCommand.cBitField.destinationOperandAddressing = MatrixAccess;
	newJmpCommand.cBitField.opcode = opcodesArray[7].opcodeNum;

	cpuFullMemory[IC].fullReg = newJmpCommand.fullCommandInt;
	IC++;

	DesinationMatrixParam.fullSymbolParam = 0;
	if(data.matrixDestination->external)
	{
		DesinationMatrixParam.symParam.encodingType = External;
		addToExternFile(data.matrixDestination);
	}
	else
		DesinationMatrixParam.symParam.encodingType = Relocatable;
	DesinationMatrixParam.symParam.addressValue = data.matrixDestination->address;

	cpuFullMemory[IC].fullReg = DesinationMatrixParam.fullSymbolParam;
	IC++;

	DestinationMatrixRegisterParam.fullRegParam = 0;
	DestinationMatrixRegisterParam.regParam.encodingType = Absolute;
	DestinationMatrixRegisterParam.regParam.regSource = data.eMatrixRegRowDestination;
	DestinationMatrixRegisterParam.regParam.regDestination = data.eMatrixRegColumnDestination;

	cpuFullMemory[IC].fullReg = DestinationMatrixRegisterParam.fullRegParam;
	IC++;
}

/*A function to add to the memory a bne command with a register as its destination parameter*/
void bneRegisterCmd(parms data)
{
	commandBitField newBneCommand;
	registersParam destinationRegistersParam;

	newBneCommand.fullCommandInt = 0;
	newBneCommand.cBitField.encodingType = Absolute;
	newBneCommand.cBitField.destinationOperandAddressing = DirectRegister;
	newBneCommand.cBitField.opcode = opcodesArray[10].opcodeNum;

	cpuFullMemory[IC].fullReg = newBneCommand.fullCommandInt;
	IC++;

	destinationRegistersParam.fullRegParam = 0;
	destinationRegistersParam.regParam.encodingType = Absolute;
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
	newBneCommand.cBitField.encodingType = Absolute;
	newBneCommand.cBitField.destinationOperandAddressing = Direct;
	newBneCommand.cBitField.opcode = opcodesArray[7].opcodeNum;

	cpuFullMemory[IC].fullReg = newBneCommand.fullCommandInt;
	IC++;

	DesinationSymbolParam.fullSymbolParam = 0;
	if(data.symbolDestination->external)
	{
		DesinationSymbolParam.symParam.encodingType = External;
		addToExternFile(data.symbolDestination);
	}
	else
		DesinationSymbolParam.symParam.encodingType = Relocatable;
	DesinationSymbolParam.symParam.addressValue = data.symbolDestination->address;

	cpuFullMemory[IC].fullReg = DesinationSymbolParam.fullSymbolParam;
	IC++;
}

/*A function to add to the memory a bne command with a matrix paramater as its destination parameter*/
void bneMatrixCmd(parms data)
{
	commandBitField newBneCommand;
	symbolParam DesinationMatrixParam;
	registersParam DestinationMatrixRegisterParam;

	newBneCommand.fullCommandInt = 0;
	newBneCommand.cBitField.encodingType = Absolute;
	newBneCommand.cBitField.destinationOperandAddressing = MatrixAccess;
	newBneCommand.cBitField.opcode = opcodesArray[7].opcodeNum;

	cpuFullMemory[IC].fullReg = newBneCommand.fullCommandInt;
	IC++;

	DesinationMatrixParam.fullSymbolParam = 0;
	if(data.matrixDestination->external)
	{
		DesinationMatrixParam.symParam.encodingType = External;
		addToExternFile(data.matrixDestination);
	}
	else
		DesinationMatrixParam.symParam.encodingType = Relocatable;
	DesinationMatrixParam.symParam.addressValue = data.matrixDestination->address;

	cpuFullMemory[IC].fullReg = DesinationMatrixParam.fullSymbolParam;
	IC++;

	DestinationMatrixRegisterParam.fullRegParam = 0;
	DestinationMatrixRegisterParam.regParam.encodingType = Absolute;
	DestinationMatrixRegisterParam.regParam.regSource = data.eMatrixRegRowDestination;
	DestinationMatrixRegisterParam.regParam.regDestination = data.eMatrixRegColumnDestination;

	cpuFullMemory[IC].fullReg = DestinationMatrixRegisterParam.fullRegParam;
	IC++;
}

/*A function to add to the memory a red command with a register as its destination parameter*/
void redRegisterCmd(parms data)
{
	commandBitField newRedCommand;
	registersParam destinationRegistersParam;

	newRedCommand.fullCommandInt = 0;
	newRedCommand.cBitField.encodingType = Absolute;
	newRedCommand.cBitField.destinationOperandAddressing = DirectRegister;
	newRedCommand.cBitField.opcode = opcodesArray[11].opcodeNum;

	cpuFullMemory[IC].fullReg = newRedCommand.fullCommandInt;
	IC++;

	destinationRegistersParam.fullRegParam = 0;
	destinationRegistersParam.regParam.encodingType = Absolute;
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
	newRedCommand.cBitField.encodingType = Absolute;
	newRedCommand.cBitField.destinationOperandAddressing = Direct;
	newRedCommand.cBitField.opcode = opcodesArray[7].opcodeNum;

	cpuFullMemory[IC].fullReg = newRedCommand.fullCommandInt;
	IC++;

	DesinationSymbolParam.fullSymbolParam = 0;
	if(data.symbolDestination->external)
	{
		DesinationSymbolParam.symParam.encodingType = External;
		addToExternFile(data.symbolDestination);
	}
	else
		DesinationSymbolParam.symParam.encodingType = Relocatable;
	DesinationSymbolParam.symParam.addressValue = data.symbolDestination->address;

	cpuFullMemory[IC].fullReg = DesinationSymbolParam.fullSymbolParam;
	IC++;
}

/*A function to add to the memory a red command with a matrix paramater as its destination parameter*/
void redMatrixCmd(parms data)
{
	commandBitField newRedCommand;
	symbolParam DesinationMatrixParam;
	registersParam DestinationMatrixRegisterParam;

	newRedCommand.fullCommandInt = 0;
	newRedCommand.cBitField.encodingType = Absolute;
	newRedCommand.cBitField.destinationOperandAddressing = MatrixAccess;
	newRedCommand.cBitField.opcode = opcodesArray[7].opcodeNum;

	cpuFullMemory[IC].fullReg = newRedCommand.fullCommandInt;
	IC++;

	DesinationMatrixParam.fullSymbolParam = 0;
	if(data.matrixDestination->external)
	{
		DesinationMatrixParam.symParam.encodingType = External;
		addToExternFile(data.matrixDestination);
	}
	else
		DesinationMatrixParam.symParam.encodingType = Relocatable;
	DesinationMatrixParam.symParam.addressValue = data.matrixDestination->address;

	cpuFullMemory[IC].fullReg = DesinationMatrixParam.fullSymbolParam;
	IC++;

	DestinationMatrixRegisterParam.fullRegParam = 0;
	DestinationMatrixRegisterParam.regParam.encodingType = Absolute;
	DestinationMatrixRegisterParam.regParam.regSource = data.eMatrixRegRowDestination;
	DestinationMatrixRegisterParam.regParam.regDestination = data.eMatrixRegColumnDestination;

	cpuFullMemory[IC].fullReg = DestinationMatrixRegisterParam.fullRegParam;
	IC++;
}

/*A function to add to the memory a prn command with a value as its destination parameter*/
void prnValueCmd(parms data)
{
	commandBitField newPrnCommand;
	valueParam destinationValueParam;

	newPrnCommand.fullCommandInt = 0;
	newPrnCommand.cBitField.encodingType = Absolute;
	newPrnCommand.cBitField.destinationOperandAddressing = Immediate;
	newPrnCommand.cBitField.opcode = opcodesArray[12].opcodeNum;

	cpuFullMemory[IC].fullReg = newPrnCommand.fullCommandInt;
	IC++;

	destinationValueParam.fullValueParam = 0;
	destinationValueParam.valParam.encodingType = Absolute;
	destinationValueParam.valParam.numericValue = data.destinationNum;

	cpuFullMemory[IC].fullReg = destinationValueParam.fullValueParam;
	IC++;
}

/*A function to add to the memory a prn command with a register as its destination parameter*/
void prnRegisterCmd(parms data)
{
	commandBitField newPrnCommand;
	registersParam destinationRegistersParam;

	newPrnCommand.fullCommandInt = 0;
	newPrnCommand.cBitField.encodingType = Absolute;
	newPrnCommand.cBitField.destinationOperandAddressing = DirectRegister;
	newPrnCommand.cBitField.opcode = opcodesArray[12].opcodeNum;

	cpuFullMemory[IC].fullReg = newPrnCommand.fullCommandInt;
	IC++;

	destinationRegistersParam.fullRegParam = 0;
	destinationRegistersParam.regParam.encodingType = Absolute;
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
	newPrnCommand.cBitField.encodingType = Absolute;
	newPrnCommand.cBitField.destinationOperandAddressing = Direct;
	newPrnCommand.cBitField.opcode = opcodesArray[7].opcodeNum;

	cpuFullMemory[IC].fullReg = newPrnCommand.fullCommandInt;
	IC++;

	DesinationSymbolParam.fullSymbolParam = 0;
	if(data.symbolDestination->external)
	{
		DesinationSymbolParam.symParam.encodingType = External;
		addToExternFile(data.symbolDestination);
	}
	else
		DesinationSymbolParam.symParam.encodingType = Relocatable;
	DesinationSymbolParam.symParam.addressValue = data.symbolDestination->address;

	cpuFullMemory[IC].fullReg = DesinationSymbolParam.fullSymbolParam;
	IC++;
}

/*A function to add to the memory a prn command with a matrix paramater as its destination parameter*/
void prnMatrixCmd(parms data)
{
	commandBitField newPrnCommand;
	symbolParam DesinationMatrixParam;
	registersParam DestinationMatrixRegisterParam;

	newPrnCommand.fullCommandInt = 0;
	newPrnCommand.cBitField.encodingType = Absolute;
	newPrnCommand.cBitField.destinationOperandAddressing = MatrixAccess;
	newPrnCommand.cBitField.opcode = opcodesArray[7].opcodeNum;

	cpuFullMemory[IC].fullReg = newPrnCommand.fullCommandInt;
	IC++;

	DesinationMatrixParam.fullSymbolParam = 0;
	if(data.matrixDestination->external)
	{
		DesinationMatrixParam.symParam.encodingType = External;
		addToExternFile(data.matrixDestination);
	}
	else
		DesinationMatrixParam.symParam.encodingType = Relocatable;
	DesinationMatrixParam.symParam.addressValue = data.matrixDestination->address;

	cpuFullMemory[IC].fullReg = DesinationMatrixParam.fullSymbolParam;
	IC++;

	DestinationMatrixRegisterParam.fullRegParam = 0;
	DestinationMatrixRegisterParam.regParam.encodingType = Absolute;
	DestinationMatrixRegisterParam.regParam.regSource = data.eMatrixRegRowDestination;
	DestinationMatrixRegisterParam.regParam.regDestination = data.eMatrixRegColumnDestination;

	cpuFullMemory[IC].fullReg = DestinationMatrixRegisterParam.fullRegParam;
	IC++;
}

/*A function to add to the memory a jsr command with a register as its destination parameter*/
void jsrRegisterCmd(parms data)
{
	commandBitField newJsrCommand;
	registersParam destinationRegistersParam;

	newJsrCommand.fullCommandInt = 0;
	newJsrCommand.cBitField.encodingType = Absolute;
	newJsrCommand.cBitField.destinationOperandAddressing = DirectRegister;
	newJsrCommand.cBitField.opcode = opcodesArray[13].opcodeNum;

	cpuFullMemory[IC].fullReg = newJsrCommand.fullCommandInt;
	IC++;

	destinationRegistersParam.fullRegParam = 0;
	destinationRegistersParam.regParam.encodingType = Absolute;
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
	newJsrCommand.cBitField.encodingType = Absolute;
	newJsrCommand.cBitField.destinationOperandAddressing = Direct;
	newJsrCommand.cBitField.opcode = opcodesArray[7].opcodeNum;

	cpuFullMemory[IC].fullReg = newJsrCommand.fullCommandInt;
	IC++;

	DesinationSymbolParam.fullSymbolParam = 0;
	if(data.symbolDestination->external)
	{
		DesinationSymbolParam.symParam.encodingType = External;
		addToExternFile(data.symbolDestination);
	}
	else
		DesinationSymbolParam.symParam.encodingType = Relocatable;
	DesinationSymbolParam.symParam.addressValue = data.symbolDestination->address;

	cpuFullMemory[IC].fullReg = DesinationSymbolParam.fullSymbolParam;
	IC++;
}

/*A function to add to the memory a jsr command with a matrix paramater as its destination parameter*/
void jsrMatrixCmd(parms data)
{
	commandBitField newJsrCommand;
	symbolParam DesinationMatrixParam;
	registersParam DestinationMatrixRegisterParam;

	newJsrCommand.fullCommandInt = 0;
	newJsrCommand.cBitField.encodingType = Absolute;
	newJsrCommand.cBitField.destinationOperandAddressing = MatrixAccess;
	newJsrCommand.cBitField.opcode = opcodesArray[7].opcodeNum;

	cpuFullMemory[IC].fullReg = newJsrCommand.fullCommandInt;
	IC++;

	DesinationMatrixParam.fullSymbolParam = 0;
	if(data.matrixDestination->external)
	{
		DesinationMatrixParam.symParam.encodingType = External;
		addToExternFile(data.matrixDestination);
	}
	else
		DesinationMatrixParam.symParam.encodingType = Relocatable;
	DesinationMatrixParam.symParam.addressValue = data.matrixDestination->address;

	cpuFullMemory[IC].fullReg = DesinationMatrixParam.fullSymbolParam;
	IC++;

	DestinationMatrixRegisterParam.fullRegParam = 0;
	DestinationMatrixRegisterParam.regParam.encodingType = Absolute;
	DestinationMatrixRegisterParam.regParam.regSource = data.eMatrixRegRowDestination;
	DestinationMatrixRegisterParam.regParam.regDestination = data.eMatrixRegColumnDestination;

	cpuFullMemory[IC].fullReg = DestinationMatrixRegisterParam.fullRegParam;
	IC++;
}

/*A function to add to the memory a rts command*/
void rtsCmd(parms data)
{
	commandBitField newRtsCommand;

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

	newRtsCommand.fullCommandInt = 0;
	newRtsCommand.cBitField.encodingType = Absolute;
	newRtsCommand.cBitField.opcode = opcodesArray[15].opcodeNum;

	cpuFullMemory[IC].fullReg = newRtsCommand.fullCommandInt;
	IC++;
}

/*A function to add a symbol to the current external file*/
void addToExternFile(pSymbol externSymbol)
{
	
	char* wierdFourNum;
	fwrite(externSymbol->label,sizeof(char),sizeof(externSymbol->label)/sizeof(char),currentExternFile);
	fwrite(tabArray,sizeof(char),2,currentExternFile);
	wierdFourNum = convertToWeirdFour(IC+1);
	fwrite(wierdFourNum,sizeof(char),sizeof(wierdFourNum)/sizeof(char),currentExternFile);
}

/*A function to add a symbol to the current entry file*/
void addToEntryFile(pSymbol entrySymbol)
{
	
	char* wierdFourNum;
	fwrite(entrySymbol->label,sizeof(char),sizeof(entrySymbol->label)/sizeof(char),currentEntryFile);
	fwrite(tabArray,sizeof(char),2,currentEntryFile);
	wierdFourNum = convertToWeirdFour(IC+1);
	fwrite(wierdFourNum,sizeof(char),sizeof(wierdFourNum)/sizeof(char),currentEntryFile);
}

/*A function to move over the lines in a file and create the extern, entry and object file*/
void moveOverFileTwo(FILE* currentFile , char* currentFileName)
{
	/*Create the current extern, entry and object file that related to the current file*/
	char* currentExternFileName;
	char* currentObjectFileName;
	char* currentEntryFileName;
	char* startLine;
	int fileChar; 
	
	int ind = 0;
	int lineNum = 0;
	int length = strlen(currentFileName);

	currentExternFileName = (char *)(malloc(((sizeof(currentFileName)/sizeof(char))+4)*sizeof(char)));
	currentEntryFileName = (char *)(malloc(((sizeof(currentFileName)/sizeof(char))+4)*sizeof(char)));
	currentObjectFileName = (char *)(malloc(((sizeof(currentFileName)/sizeof(char))+3)*sizeof(char)));
	
	while(ind < length)
	{
		currentExternFileName[ind] = (*currentFileName);
		currentEntryFileName[ind] = (*currentFileName);
		currentObjectFileName[ind] = (*currentFileName);
		currentFileName++;
		ind++;
	}

	currentExternFileName[ind] = '.';
	currentExternFileName[ind+1] = 'e';
	currentExternFileName[ind+2] = 'x';
	currentExternFileName[ind+3] = 't';
	currentExternFileName[ind+4] = '\0';

	currentEntryFileName[ind] = '.';
	currentEntryFileName[ind+1] = 'e';
	currentEntryFileName[ind+2] = 'n';
	currentEntryFileName[ind+3] = 't';
	currentEntryFileName[ind+4] = '\0';

	currentObjectFileName[ind] = '.';
	currentObjectFileName[ind+1] = 'o';
	currentObjectFileName[ind+2] = 'b';
	currentObjectFileName[ind+3] = '\0';

	currentExternFile = fopen(currentExternFileName , "w");
	currentEntryFile = fopen(currentEntryFileName , "w");
	currentObjectFile = fopen(currentObjectFileName , "w");
	readdressSymbolTable();
	IC = 100;
	startLine = (char*)(malloc(sizeof(char)*MAXLINE));
	ind = 0;
	lineNum = 1;
	while((fileChar = fgetc(currentFile)))
	{
		if(fileChar == '\n')
		{
			startLine[ind] = '\0';
			analizeLineSecTransition(startLine , lineNum);
			ind = 0;
			lineNum++;
			continue;
		}
		if (fileChar == EOF)
		{
			if(ind > 0)
			{
				startLine[ind] = '\0';
				analizeLineSecTransition(startLine, lineNum);
				ind = 0;
				lineNum++;
			}
			break;
		}
		else
            		startLine[ind++] = (char)fileChar;
	}

	writeObjectFile();
}

void writeObjectFile()
{
	int moveObjectFile = 0;
	char* NumToWierdFour;
	char* DataToWierdFour;
	char* newLine = "\n";
	NumToWierdFour = convertToWeirdFour(IC - 100);
	DataToWierdFour = convertToWeirdFour(DC);
	fwrite(NumToWierdFour,sizeof(char),strlen(NumToWierdFour),currentObjectFile);
	fwrite(tabArray,sizeof(char),strlen(tabArray),currentObjectFile);
	fwrite(DataToWierdFour,sizeof(char),strlen(DataToWierdFour),currentObjectFile);
	for(moveObjectFile = 100;  moveObjectFile < IC+DC; moveObjectFile++)
	{
		fwrite(newLine,sizeof(char),strlen(newLine),currentObjectFile);
		NumToWierdFour = convertToWeirdFour(moveObjectFile);
		fwrite(NumToWierdFour,sizeof(char),strlen(NumToWierdFour),currentObjectFile);
		fwrite(tabArray,sizeof(char),strlen(tabArray),currentObjectFile);
		NumToWierdFour = convertToWeirdFour(cpuFullMemory[moveObjectFile].fullReg);
		fwrite(NumToWierdFour,sizeof(char),strlen(NumToWierdFour),currentObjectFile);
	}

	free(NumToWierdFour);
	free(DataToWierdFour);
}

/*A function to get the parameter type a function return by two addressing method*/
eParametersType assignTwoCommandParametersType(eAddressingMethod firstParam , eAddressingMethod secondParam)
{
	if(firstParam == Immediate)
	{
		switch(secondParam)
		{
			case Immediate: return VALUE_VALUE; break;
			case Direct: return VALUE_SYMBOL; break;
			case MatrixAccess: return VALUE_MATRIX; break;
			case DirectRegister: return VALUE_REGISTER; break;
		}
	}
	if(firstParam == Direct)
	{
		switch(secondParam)
		{
			case Immediate: return SYMBOL_VALUE; break;
			case Direct: return SYMBOL_SYMBOL; break;
			case MatrixAccess: return SYMBOL_MATRIX; break;
			case DirectRegister: return SYMBOL_REGISTER; break;
		}
	}
	if(firstParam == MatrixAccess)
	{
		switch(secondParam)
		{
			case Immediate: return MATRIX_VALUE; break;
			case Direct: return MATRIX_SYMBOL; break;
			case MatrixAccess: return MATRIX_MATRIX; break;
			case DirectRegister: return MATRIX_REGISTER; break;
		}
	}
	if(firstParam == DirectRegister)
	{
		switch(secondParam)
		{
			case Immediate: return REGISTER_VALUE; break;
			case Direct: return REGISTER_SYMBOL; break;
			case MatrixAccess: return REGISTER_MATRIX; break;
			case DirectRegister: return TWO_REGISTER; break;
		}
	}
	return NONE_PARAMETERS;
}

/*A function to analize a line in the the second transition*/
int analizeLineSecTransition(char *line , int lineNum)
{
	char cmdName[5];
	parms funcParms;
	cmd currentCmd;
	eParametersType funcParametersType = NONE_PARAMETERS;
	unsigned int numOfParams;
	eAddressingMethod firstParamAddressingMethod = Immediate;
	int count = 0;

	/*Skip white spaces*/
	while((*line) == ' ' || (*line) == '\t')
		line++;
	
	/*find if this line is an entry or an extern line*/
	if((strncmp(line,ENTRY,sizeof(ENTRY)/sizeof(char) - 1) == 0) || (strncmp(line,EXTERN,sizeof(EXTERN)/sizeof(char) - 1) == 0)
		|| (strncmp(line,DATA,sizeof(DATA)/sizeof(char) - 1) == 0) || (strncmp(line,STRING,sizeof(STRING)/sizeof(char) - 1) == 0)
		|| (strncmp(line,MAT,sizeof(MAT)/sizeof(char) - 1) == 0))
	{
		return 1;
	}
	else
	{
		/*find if there is label*/
		if((strchr(line , ':') != NULL) && ((strchr(line , ':') && strchr(line , '"') == NULL) || (strchr(line , ':') < strchr(line , '"'))))
		{
			pSymbol currentLabel;
			char* label;
			label = (char *)malloc((strchr(line , ':') - line) * sizeof(char));
			count = 0;
			/*Get label name*/
			while((*line) != ':' && (*line) != ' ' && (*line) != '\t')
			{
				label[count] = (*line);
				line++;
				count++;
			}
			label[count] = '\0';
			/*Find if the label is an action line*/
			currentLabel = findSymbolByLabel(label);
			if(!(currentLabel->action))
			{
				return 1;
			}
		}
		/*Skip white spaces*/
		while((*line) == ' ' || (*line) == '\t')
			line++;
		if((*line) == ':')
			line++;
		/*Skip white spaces*/
		while((*line) == ' ' || (*line) == '\t')
			line++;
		/*Get the command name in the line*/
		if(lineNum == 3)
			lineNum++;
		count = 0;
		while((*line) != ' ' && (*line) != '\t' && count<=3)
		{
			cmdName[count] = (*line);
			line++;
			count++;
		}
		cmdName[count] = '\0';
		numOfParams = getNumOfParamsOfOpCode(cmdName);
		/*Skip white spaces*/
		while((*line) == ' ' || (*line) == '\t')
				line++;
		if(numOfParams != 0)
		{
			if((*line) == '#')
			{
				/*get a number parameter*/
				char* number;
				line++;
				number = (char *)malloc(MAXNUMBERSIZE * sizeof(char));
				count = 0;
				while((*line) != ' ' && (*line) != '\t' && (*line) != ',')
				{
					number[count] = (*line);
					line++;
					count++;
				}
				number[count] = '\0';
				if(numOfParams == 2)
				{
					funcParms.sourceNum = atoi(number);
					firstParamAddressingMethod = Immediate;
				}
				else
				{
					if(numOfParams == 1)
					{
						funcParms.destinationNum = atoi(number);
						funcParametersType = ONE_VALUE;
					}
				}
				free(number);
			}
			else
			{
				char word[MAXLABEL+1];
				count = 0;
				if(toupper((*line)) == 'R')
				{
					word[count] = 'R';
					count++;
					line++;
					if((*line) >='0' && (*line) <= '7')
					{
						word[count] = (*line);
						count++;
						line++;
						if((*line) == ' ' || (*line) == '\t' || (*line) == ',' || strlen(line) == 0)
						{
							eCpuRegisters currentRegister;
							switch((word[count - 1]) - '0')
							{
								case 0: currentRegister = r0; break;
								case 1: currentRegister = r1; break;
								case 2: currentRegister = r2; break;
								case 3: currentRegister = r3; break;
								case 4: currentRegister = r4; break;
								case 5: currentRegister = r5; break;
								case 6: currentRegister = r6; break;
								case 7: currentRegister = r7; break;
							}
							if(numOfParams == 2)
							{
								funcParms.eRegSource = currentRegister;
								firstParamAddressingMethod = DirectRegister;
							}
							else
							{
								if(numOfParams == 1)
								{
									funcParms.eRegDestination = currentRegister;
									funcParametersType = ONE_REGISTER;
								}
							}
						}
					}
				}
				if(funcParametersType != ONE_REGISTER && firstParamAddressingMethod != DirectRegister)
				{
					while((*line) != ' ' && (*line) != '\t' && (*line) != '[' && strlen(line) > 0)
					{
						word[count] = (*line);
						line++;
						count++;
					}
					word[count] = '\0';
					while((*line) == ' ' || (*line) == '\t')
						line++;
					if((*line) == '[')
					{
						eCpuRegisters registerSource;
						eCpuRegisters registerDestination;
						line++;
						while((*line) == ' ' || (*line) == '\t')
							line++;
						if(toupper((*line)) == 'R')
							line++;
						switch((*line) - '0')
						{
							case 0: registerSource = r0; break;
							case 1: registerSource = r1; break;
							case 2: registerSource = r2; break;
							case 3: registerSource = r3; break;
							case 4: registerSource = r4; break;
							case 5: registerSource = r5; break;
							case 6: registerSource = r6; break;
							case 7: registerSource = r7; break;
						}
						while((*line) == ' ' || (*line) == '\t')
							line++;
						line++;
						if((*line) == ']')
							line++;
						if((*line) == '[')
							line++;
						if(toupper((*line)) == 'R')
							line++;
						switch((*line) - '0')
						{
							case 0: registerDestination = r0; break;
							case 1: registerDestination = r1; break;
							case 2: registerDestination = r2; break;
							case 3: registerDestination = r3; break;
							case 4: registerDestination = r4; break;
							case 5: registerDestination = r5; break;
							case 6: registerDestination = r6; break;
							case 7: registerDestination = r7; break;
						}
						line++;
						if((*line) == ']')
							line++;
						if(numOfParams == 2)
						{
							funcParms.matrixSource = findSymbolByLabel(word);
							if(funcParms.matrixSource == NULL)
								addToErrorList(&errorList, &errorListLast, LABEL_INPUT_NOT_EXSIST, lineNum);
							funcParms.eMatrixRegRowSource = registerSource;
							funcParms.eMatrixRegColumnSource = registerDestination;
							firstParamAddressingMethod = MatrixAccess;
						}
						else
						{
							if(numOfParams == 1)
							{
								funcParms.matrixDestination = findSymbolByLabel(word);
								if(funcParms.matrixDestination == NULL)
									addToErrorList(&errorList, &errorListLast, LABEL_INPUT_NOT_EXSIST, lineNum);
								funcParms.eMatrixRegRowDestination = registerSource;
								funcParms.eMatrixRegColumnDestination = registerDestination;
								funcParametersType = ONE_MATRIX;
							}
						}
					}
					else
					{
						if(numOfParams == 2)
						{
							funcParms.symbolSource = findSymbolByLabel(word);
							if(funcParms.symbolSource == NULL)
								addToErrorList(&errorList, &errorListLast, LABEL_INPUT_NOT_EXSIST, lineNum);
							firstParamAddressingMethod = Direct;
						}
						else
						{
							if(numOfParams == 1)
							{
								funcParms.symbolDestination = findSymbolByLabel(word);
								if(funcParms.symbolDestination == NULL)
									addToErrorList(&errorList, &errorListLast, LABEL_INPUT_NOT_EXSIST, lineNum);
								funcParametersType = ONE_SYMBOL;
							}
						}
					}
				}
			}
			if(numOfParams == 2)
			{
				while((*line) == ' ' || (*line) == '\t')
					line++;
				if((*line) == ',')
				{
					line++;
				}
				/*Skip white spaces*/
				while((*line) == ' ' || (*line) == '\t')
					line++;
				if((*line) == '#')
				{
					/*Get a number parameter from line as destination parameter*/
					char* number;
					line++;
					count = 0;
					number = (char *)malloc(MAXNUMBERSIZE * sizeof(char));
					while((*line) != ' ' && (*line) != '\t')
					{
						number[count] = (*line);
						line++;
						count++;
					}
					number[count] = '\0';
					funcParms.destinationNum = atoi(number);
					funcParametersType = assignTwoCommandParametersType(firstParamAddressingMethod , Immediate);
					free(number);
				}
				else
				{
					char word[MAXLABEL+1];
					count = 0;
					if(toupper((*line)) == 'R')
					{
						word[count] = 'R';
						count++;
						line++;
						if((*line) >='0' && (*line) <= '7')
						{
							word[count] = (*line);
							count++;
							line++;
							if( (*line) == ' ' || (*line) == '\t' || (*line) == '\n' || (int)(*line) == EOF || (*line) == 0)
							{
								eCpuRegisters currentRegister;
								switch(word[count - 1] - '0')
								{
									case 0: currentRegister = r0; break;
									case 1: currentRegister = r1; break;
									case 2: currentRegister = r2; break;
									case 3: currentRegister = r3; break;
									case 4: currentRegister = r4; break;
									case 5: currentRegister = r5; break;
									case 6: currentRegister = r6; break;
									case 7: currentRegister = r7; break;
								}
								funcParms.eRegDestination = currentRegister;
								funcParametersType = assignTwoCommandParametersType(firstParamAddressingMethod , DirectRegister);
							}
						}
					}
					if(funcParametersType != VALUE_REGISTER && funcParametersType != MATRIX_REGISTER 
						&& funcParametersType != SYMBOL_REGISTER && funcParametersType != TWO_REGISTER)
					{
						if(lineNum == 4)
							lineNum = 4;
						while((*line) != ' ' && (*line) != '\t' && (*line) != '\n' && (int)(*line) != EOF && (*line) != '[' && strlen(line)> 0)
						{
							word[count] = (*line);
							line++;
							count++;
						}
						word[count] = '\0';
						while((*line) == ' ' || (*line) == '\t')
							line++;
						if((*line) == '[')
						{
							eCpuRegisters registerSource;
							eCpuRegisters registerDestination;
							while((*line) == ' ' || (*line) == '\t')
								line++;
							line++;
							switch((*line) - '0')
							{
								case 0: registerSource = r0; break;
								case 1: registerSource = r1; break;
								case 2: registerSource = r2; break;
								case 3: registerSource = r3; break;
								case 4: registerSource = r4; break;
								case 5: registerSource = r5; break;
								case 6: registerSource = r6; break;
								case 7: registerSource = r7; break;
							}
							while((*line) == ' ' || (*line) == '\t')
								line++;
							line++;
							switch((*line) - '0')
							{
								case 0: registerDestination = r0; break;
								case 1: registerDestination = r1; break;
								case 2: registerDestination = r2; break;
								case 3: registerDestination = r3; break;
								case 4: registerDestination = r4; break;
								case 5: registerDestination = r5; break;
								case 6: registerDestination = r6; break;
								case 7: registerDestination = r7; break;
							}
							funcParms.matrixDestination = findSymbolByLabel(word);
							if(funcParms.matrixDestination == NULL)
								addToErrorList(&errorList, &errorListLast, LABEL_INPUT_NOT_EXSIST, lineNum);
							funcParms.eMatrixRegRowDestination = registerSource;
							funcParms.eMatrixRegColumnDestination = registerDestination;
							funcParametersType = assignTwoCommandParametersType(firstParamAddressingMethod , MatrixAccess);
						}
						else
						{
							funcParms.symbolDestination = findSymbolByLabel(word);
							if(funcParms.symbolDestination == NULL)
								addToErrorList(&errorList, &errorListLast, LABEL_INPUT_NOT_EXSIST, lineNum);
							funcParametersType = assignTwoCommandParametersType(firstParamAddressingMethod , Direct);
						}
					}
				}
			}
		}
		else
		{
			funcParametersType = NONE_PARAMETERS;
		}
		/*Get command to preform and preform it*/
		currentCmd = getCmdToPreform(cmdName , funcParametersType);
		currentCmd.func(funcParms);
	}
	return 0;
}

/*Find the current command to preform according to the command name and recived parameters*/
cmd getCmdToPreform(char* cmdName , eParametersType funcParametersType)
{
	int i;
	int cmdId;
	cmd* cmds = NULL;
	/*find the current command array*/
	for (i=0;i<16;i++)
	{

		if(strcmp(cmdName,opcodesArray[i].opcodeName)==0)
		{
			cmdId = opcodesArray[i].opcodeNum;
		}
	}

	switch (cmdId)
	{
		case 0: cmds = movs; break;
		case 1: cmds = cmps; break;
		case 2: cmds = adds; break;
		case 3: cmds = subs; break;
		case 4: cmds = nots; break;
		case 5: cmds = clrs; break;
		case 6: cmds = leas; break;
		case 7: cmds = incs; break;
		case 8: cmds = decs; break;
		case 9: cmds = jmps; break;
		case 10: cmds = bnes; break;
		case 11: cmds = reds; break;
		case 12: cmds = prns; break;
		case 13: cmds = jsrs; break;
		case 14: cmds = rtss; break;
		case 15: cmds = stops; break;
	}

	/*Find the current command in the command array*/
	while(cmds)
	{
		if(cmds->paramFunc == funcParametersType)
		{
			return (*cmds);
		}
		cmds++;
	}
	return (*cmds);

}




