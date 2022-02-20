# A homework problem solution for the CS:APP3e
#
# Copyright (C) 2022 Tongjie Liu <tongjieandliu@gmail.com>.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

#/* $begin pipe-all-hcl */
####################################################################
#    HCL Description of Control for Pipelined Y86-64 Processor     #
#    Copyright (C) Randal E. Bryant, David R. O'Hallaron, 2014     #
####################################################################




####################################################################
#    C Include's.  Don't alter these                               #
####################################################################

quote '#include <stdio.h>'
quote '#include "isa.h"'
quote '#include "pipeline.h"'
quote '#include "stages.h"'
quote '#include "sim.h"'
quote 'int sim_main(int argc, char *argv[]);'
quote 'int main(int argc, char *argv[]){return sim_main(argc,argv);}'

####################################################################
#    Declarations.  Do not change/remove/delete any of these       #
####################################################################

##### Symbolic representation of Y86-64 Instruction Codes #############
wordsig INOP 	'I_NOP'
wordsig IHALT	'I_HALT'
wordsig IRRMOVQ	'I_RRMOVQ'
wordsig IIRMOVQ	'I_IRMOVQ'
wordsig IRMMOVQ	'I_RMMOVQ'
wordsig IMRMOVQ	'I_MRMOVQ'
wordsig IOPQ	'I_ALU'
wordsig IJXX	'I_JMP'
wordsig ICALL	'I_CALL'
wordsig IRET	'I_RET'
wordsig IPUSHQ	'I_PUSHQ'
wordsig IPOPQ	'I_POPQ'

##### Symbolic represenations of Y86-64 function codes            #####
wordsig FNONE    'F_NONE'        # Default function code

##### Symbolic representation of Y86-64 Registers referenced      #####
wordsig RRSP     'REG_RSP'    	     # Stack Pointer
wordsig RNONE    'REG_NONE'   	     # Special value indicating "no register"

##### ALU Functions referenced explicitly ##########################
wordsig ALUADD	'A_ADD'		     # ALU should add its arguments

##### Possible instruction status values                       #####
wordsig SBUB	'STAT_BUB'	# Bubble in stage
wordsig SAOK	'STAT_AOK'	# Normal execution
wordsig SADR	'STAT_ADR'	# Invalid memory address
wordsig SINS	'STAT_INS'	# Invalid instruction
wordsig SHLT	'STAT_HLT'	# Halt instruction encountered

##### Signals that can be referenced by control logic ##############

##### Pipeline Register F ##########################################

wordsig F_predPC 'pc_curr->pc'	     # Predicted value of PC

##### Intermediate Values in Fetch Stage ###########################

wordsig imem_icode  'imem_icode'      # icode field from instruction memory
wordsig imem_ifun   'imem_ifun'       # ifun  field from instruction memory
wordsig f_icode	'if_id_next->icode'  # (Possibly modified) instruction code
wordsig f_ifun	'if_id_next->ifun'   # Fetched instruction function
wordsig f_valC	'if_id_next->valc'   # Constant data of fetched instruction
wordsig f_valP	'if_id_next->valp'   # Address of following instruction
boolsig imem_error 'imem_error'	     # Error signal from instruction memory
boolsig instr_valid 'instr_valid'    # Is fetched instruction valid?

##### Pipeline Register D ##########################################
wordsig D_icode 'if_id_curr->icode'   # Instruction code
wordsig D_rA 'if_id_curr->ra'	     # rA field from instruction
wordsig D_rB 'if_id_curr->rb'	     # rB field from instruction
wordsig D_valP 'if_id_curr->valp'     # Incremented PC

##### Intermediate Values in Decode Stage  #########################

wordsig d_srcA	 'id_ex_next->srca'  # srcA from decoded instruction
wordsig d_srcB	 'id_ex_next->srcb'  # srcB from decoded instruction
wordsig d_rvalA 'd_regvala'	     # valA read from register file
wordsig d_rvalB 'd_regvalb'	     # valB read from register file

##### Pipeline Register E ##########################################
wordsig E_icode 'id_ex_curr->icode'   # Instruction code
wordsig E_ifun  'id_ex_curr->ifun'    # Instruction function
wordsig E_valC  'id_ex_curr->valc'    # Constant data
wordsig E_srcA  'id_ex_curr->srca'    # Source A register ID
wordsig E_valA  'id_ex_curr->vala'    # Source A value
wordsig E_srcB  'id_ex_curr->srcb'    # Source B register ID
wordsig E_valB  'id_ex_curr->valb'    # Source B value
wordsig E_dstE 'id_ex_curr->deste'    # Destination E register ID
wordsig E_dstM 'id_ex_curr->destm'    # Destination M register ID

##### Intermediate Values in Execute Stage #########################
wordsig e_valE 'ex_mem_next->vale'	# valE generated by ALU
boolsig e_Cnd 'ex_mem_next->takebranch' # Does condition hold?
wordsig e_dstE 'ex_mem_next->deste'      # dstE (possibly modified to be RNONE)

##### Pipeline Register M                  #########################
wordsig M_stat 'ex_mem_curr->status'     # Instruction status
wordsig M_icode 'ex_mem_curr->icode'	# Instruction code
wordsig M_ifun  'ex_mem_curr->ifun'	# Instruction function
wordsig M_valA  'ex_mem_curr->vala'      # Source A value
wordsig M_dstE 'ex_mem_curr->deste'	# Destination E register ID
wordsig M_valE  'ex_mem_curr->vale'      # ALU E value
wordsig M_dstM 'ex_mem_curr->destm'	# Destination M register ID
boolsig M_Cnd 'ex_mem_curr->takebranch'	# Condition flag
boolsig dmem_error 'dmem_error'	        # Error signal from instruction memory

##### Intermediate Values in Memory Stage ##########################
wordsig m_valM 'mem_wb_next->valm'	# valM generated by memory
wordsig m_stat 'mem_wb_next->status'	# stat (possibly modified to be SADR)

##### Pipeline Register W ##########################################
wordsig W_stat 'mem_wb_curr->status'     # Instruction status
wordsig W_icode 'mem_wb_curr->icode'	# Instruction code
wordsig W_dstE 'mem_wb_curr->deste'	# Destination E register ID
wordsig W_valE  'mem_wb_curr->vale'      # ALU E value
wordsig W_dstM 'mem_wb_curr->destm'	# Destination M register ID
wordsig W_valM  'mem_wb_curr->valm'	# Memory M value

####################################################################
#    Control Signal Definitions.                                   #
####################################################################

################ Fetch Stage     ###################################

## What address should instruction be fetched at
word f_pc = [
	# Mispredicted branch.  Fetch at incremented PC
	M_icode == IJXX && !M_Cnd : M_valA;
	# Completion of RET instruction
	W_icode == IRET : W_valM;
	# Default: Use predicted value of PC
	1 : F_predPC;
];

## Determine icode of fetched instruction
word f_icode = [
	imem_error : INOP;
	1: imem_icode;
];

# Determine ifun
word f_ifun = [
	imem_error : FNONE;
	1: imem_ifun;
];

# Is instruction valid?
bool instr_valid = f_icode in 
	{ INOP, IHALT, IRRMOVQ, IIRMOVQ, IRMMOVQ, IMRMOVQ,
	  IOPQ, IJXX, ICALL, IRET, IPUSHQ, IPOPQ };

# Determine status code for fetched instruction
word f_stat = [
	imem_error: SADR;
	!instr_valid : SINS;
	f_icode == IHALT : SHLT;
	1 : SAOK;
];

# Does fetched instruction require a regid byte?
bool need_regids =
	f_icode in { IRRMOVQ, IOPQ, IPUSHQ, IPOPQ, 
		     IIRMOVQ, IRMMOVQ, IMRMOVQ };

# Does fetched instruction require a constant word?
bool need_valC =
	f_icode in { IIRMOVQ, IRMMOVQ, IMRMOVQ, IJXX, ICALL };

# Predict next value of PC
word f_predPC = [
	f_icode in { IJXX, ICALL } : f_valC;
	1 : f_valP;
];

################ Decode Stage ######################################


## What register should be used as the A source?
word d_srcA = [
	D_icode in { IRRMOVQ, IRMMOVQ, IOPQ, IPUSHQ  } : D_rA;
	D_icode in { IPOPQ, IRET } : RRSP;
	1 : RNONE; # Don't need register
];

## What register should be used as the B source?
word d_srcB = [
	D_icode in { IOPQ, IRMMOVQ, IMRMOVQ  } : D_rB;
	D_icode in { IPUSHQ, IPOPQ, ICALL, IRET } : RRSP;
	1 : RNONE;  # Don't need register
];

## What register should be used as the E destination?
word d_dstE = [
	D_icode in { IRRMOVQ, IIRMOVQ, IOPQ} : D_rB;
	D_icode in { IPUSHQ, IPOPQ, ICALL, IRET } : RRSP;
	1 : RNONE;  # Don't write any register
];

## What register should be used as the M destination?
word d_dstM = [
	D_icode in { IMRMOVQ, IPOPQ } : D_rA;
	1 : RNONE;  # Don't write any register
];

## What should be the A value?
##  DO NOT MODIFY THE FOLLOWING CODE.
## No forwarding.  valA is either valP or value from register file
word d_valA = [
	D_icode in { ICALL, IJXX } : D_valP; # Use incremented PC
	1 : d_rvalA;  # Use value read from register file
];

## No forwarding.  valB is value from register file
word d_valB = d_rvalB;

################ Execute Stage #####################################

## Select input A to ALU
word aluA = [
	E_icode in { IRRMOVQ, IOPQ } : E_valA;
	E_icode in { IIRMOVQ, IRMMOVQ, IMRMOVQ } : E_valC;
	E_icode in { ICALL, IPUSHQ } : -8;
	E_icode in { IRET, IPOPQ } : 8;
	# Other instructions don't need ALU
];

## Select input B to ALU
word aluB = [
	E_icode in { IRMMOVQ, IMRMOVQ, IOPQ, ICALL, 
		     IPUSHQ, IRET, IPOPQ } : E_valB;
	E_icode in { IRRMOVQ, IIRMOVQ } : 0;
	# Other instructions don't need ALU
];

## Set the ALU function
word alufun = [
	E_icode == IOPQ : E_ifun;
	1 : ALUADD;
];

## Should the condition codes be updated?
bool set_cc = E_icode == IOPQ &&
	# State changes only during normal operation
	!m_stat in { SADR, SINS, SHLT } && !W_stat in { SADR, SINS, SHLT };

## Generate valA in execute stage
word e_valA = E_valA;    # Pass valA through stage

## Set dstE to RNONE in event of not-taken conditional move
word e_dstE = [
	E_icode == IRRMOVQ && !e_Cnd : RNONE;
	1 : E_dstE;
];

################ Memory Stage ######################################

## Select memory address
word mem_addr = [
	M_icode in { IRMMOVQ, IPUSHQ, ICALL, IMRMOVQ } : M_valE;
	M_icode in { IPOPQ, IRET } : M_valA;
	# Other instructions don't need address
];

## Set read control signal
bool mem_read = M_icode in { IMRMOVQ, IPOPQ, IRET };

## Set write control signal
bool mem_write = M_icode in { IRMMOVQ, IPUSHQ, ICALL };

#/* $begin pipe-m_stat-hcl */
## Update the status
word m_stat = [
	dmem_error : SADR;
	1 : M_stat;
];
#/* $end pipe-m_stat-hcl */

## Set E port register ID
word w_dstE = W_dstE;

## Set E port value
word w_valE = W_valE;

## Set M port register ID
word w_dstM = W_dstM;

## Set M port value
word w_valM = W_valM;

## Update processor status
word Stat = [
	W_stat == SBUB : SAOK;
	1 : W_stat;
];




################ Pipeline Register Control #########################
#####################################################################
#           modifications for Homework Problem 4.53 start           #
#####################################################################

#	We could combine load/use hazard and other data hazrds into a single
# condition, namely "data hazard". Data hazard happens when an instruction
# in the decode stage try to reads registers(from the register file, clocked
# registers are not included) which are going to be updated by insturctions
# in the later stages(i.e. execute stage, memory stage, and write back stage).
#
# Condition			Trigger
# Data hazard		e_dstE in {d_srcA, d_srcB} ||
#			M_dstE in {d_srcA, d_srcB} ||
#			M_dstM in {d_srcA, d_srcB} ||
#			W_dstE in {d_srcA, d_srcB} ||
#			W_dstM in {d_srcA, d_srcB}
#
#	Note that M_dstE is not checked in the data forwarding logic, since
# there is no valM in execute stage. But after we change from data forwarding
# method to stalling method, a instruction in the execute stage will compute
# a new value for valM in the memory stage, and this value should be consistent
# with the value read by the instruction in the decode stage when the first
# instruction we mentioned is in the execute stage, which is guaranteed by the
# Y86-64 ISA.
#
# 	Besides, M_dstE was originally checked in load/use hazard in the book,
# which is now part of "data hazard" class.
#
#				Pipeline register
# Condition		F	D	E	M	W
# Data hazard         stall   stall   bubble  normal  normal
#
# 	For handling combinations of control conditions, we can see that there
# are only 2 control conditions that may interact with data hazard left for us
# to handle, namely processing ret and mispredicted branch.
#
#	Pipeline states for data hazard fall into a number of situations:
#	W	write		write	write		write
#	M	write	write		write			write
#	E	write	write	write		write
#	D	read	read	read	read	read	read	read
#                1       2       3       4       5       6       7
#
# and processing ret falls into:
# 	W
# 	M			ret
# 	E		ret	bubble
# 	D	ret	bubble	bubble
#                1       2       3
#
# but mispredicted branch only has 1 situation:
# 	W
# 	M
# 	E	jxx
# 	D
#
# 	As you can see, situation 2 and 3 of processing ret don't read the
# register file in the decode stage, since bubble does not read register file.
# Hence, there is only one situation of processing ret left, namely the first
# one.
#
# 	Combine the pipeline register modes of the first situation of pro-
# cessing ret and data hazard, we get the following result:
# 				Pipeline register
# Condition		F	D		E	M	W
# combination 1       stall stall/bubble     bubble   normal  normal
#
#	The ret instruction should wait in the decode stage until the register
# file has finished all the writing operations from instructions after the
# decode stage. Hence we choose stall as the answer to the decode pipeline
# register.
#
# 				Pipeline register
# Condition		F	D		E	M	W
# combination 1       stall   stall           bubble   normal  normal
#
# 	The combination of mispredicted branch and data hazard is quite similar
# to combination 1:
#
# 				Pipeline register
# Condition		F	D		E	M	W
# combination 2       stall stall/bubble     bubble   normal  normal
#
# 	In a mispredicted branch situation, the instruction in the decode stage
# is mispredicted. In other words, it should've never been executed. Therefore,
# it need to be replaced by a bubble. Note that, although the fetch pipeline
# register is stalled, the Select PC logic block will receive the correct valP
# after a mispredicted branch has been detected, and the fetch stage will try
# to execute the correct instruction, then Predict PC logic block will try to
# update predPC in the fetch pipeline register with the next intsurction of
# the that instruction.
#
# 				Pipeline register
# Condition		F	D		E	M	W
# combination 2       stall   bubble         bubble   normal  normal
#
# 	Unfortunately, there is still a third combination, i.e. data hazard +
# processing ret + mispredicted branch. Since the ret instruction in the decode
# stage is mispredicted, it should be discarded. Inserting a bubble in the
# decode stage is the right move.
#
#	Here is the complete special control cases, except exception handlings:
# 				Pipeline register
# Condition			F	D		E	M	W
# Data hazard                 stall   stall          bubble   normal  normal
# processing ret              stall   bubble         normal   normal  normal
# mispredicted branch         normal  bubble         bubble   normal  normal
# combination 1               stall   stall          bubble   normal  normal
# combination 2               stall   bubble         bubble   normal  normal
# combination 3               stall   bubble         bubble   normal  normal
#
# 	Note that, the orginal 2 combinations namely combination A and B are
# not listed here, since combination A needs no special care, and combination
# 2 is no longer existed after load/use hazard is handled like normal data
# hazards in our discussion.
#
# 	To have a better understanding of these 3 new combinations, we could
# see it from a different prespective: the 3 more simpler special control cases
# have different priorities over decode stage when combining together, namely
# mispredicted branch > data hazard > processing ret.

bool F_bubble = 0;


bool F_stall =
	# processing ret
	IRET in { D_icode, E_icode, M_icode } ||
	# 	A data hazard.
	#
	#	Unfortunately, the solution in the comment above does not work.
	# 
	#	If we take a look at the output of standard psim with verbosity
	# level of 2, we could discover that the processor use nop instruction
	# to fill up stages that are empty when it starts. Obviously, nop is a
	# instruction that does not read or write any registers. Thus, all these
	# signals are initialized to RNONE when the processor starts, and false
	# data hazards are always detected by the pipeline control logic, which
	# makes the processor stalling forever(fetch pipeline register stalls,
	# and decode pipeline register stalls too).
	#
	# 	Moreover, there are other false data hazards may be detected.
	# Since an instruction that doesn't read at least one register in the
	# decode stage has at least one RNONE in d_srcA or d_srcB, and in later
	# stages there may be at least one insturction that doesn't write at
	# least one register has at least one RNONE in e_dstE, E_dstM, M_dstE,
	# M_dstM, W_dstE or W_dstM. This can happen at any time, not only when
	# the processor starts.
	#
	# 	In spite of that, a simple modification is enough. The reason
	# behind this is that the first case is a part of the second.
	(
		(e_dstE in {d_srcA, d_srcB} && e_dstE != RNONE) ||
		(E_dstM in {d_srcA, d_srcB} && E_dstM != RNONE) ||
		(M_dstE in {d_srcA, d_srcB} && M_dstE != RNONE) ||
		(M_dstM in {d_srcA, d_srcB} && M_dstM != RNONE) ||
		(W_dstE in {d_srcA, d_srcB} && W_dstE != RNONE) ||
		(W_dstM in {d_srcA, d_srcB} && W_dstM != RNONE)
	);




# data hazard but no mispredicted branch
bool D_stall = 
	# A data hazard. We make the same modification.
	(
		(e_dstE in {d_srcA, d_srcB} && e_dstE != RNONE) ||
		(E_dstM in {d_srcA, d_srcB} && E_dstM != RNONE) ||
		(M_dstE in {d_srcA, d_srcB} && M_dstE != RNONE) ||
		(M_dstM in {d_srcA, d_srcB} && M_dstM != RNONE) ||
		(W_dstE in {d_srcA, d_srcB} && W_dstE != RNONE) ||
		(W_dstM in {d_srcA, d_srcB} && W_dstM != RNONE)
	) &&
	# always cancel mispredicted instructions
	!(E_icode == IJXX && !e_Cnd);


bool D_bubble =
	# always cancel mispredicted instructions
	(E_icode == IJXX && !e_Cnd) ||
	# processing ret but no data hazard
	(
		IRET in { D_icode, E_icode, M_icode } &&
		# A data hazard. We make the same modification.
		!(
			(e_dstE in {d_srcA, d_srcB} && e_dstE != RNONE) ||
			(E_dstM in {d_srcA, d_srcB} && E_dstM != RNONE) ||
			(M_dstE in {d_srcA, d_srcB} && M_dstE != RNONE) ||
			(M_dstM in {d_srcA, d_srcB} && M_dstM != RNONE) ||
			(W_dstE in {d_srcA, d_srcB} && W_dstE != RNONE) ||
			(W_dstM in {d_srcA, d_srcB} && W_dstM != RNONE)
		)
	);




bool E_stall = 0;


bool E_bubble =
	# mispredicted branch
	(E_icode == IJXX && !e_Cnd) ||
	# A data hazard. We make the same modification.
	(
		(e_dstE in {d_srcA, d_srcB} && e_dstE != RNONE) ||
		(E_dstM in {d_srcA, d_srcB} && E_dstM != RNONE) ||
		(M_dstE in {d_srcA, d_srcB} && M_dstE != RNONE) ||
		(M_dstM in {d_srcA, d_srcB} && M_dstM != RNONE) ||
		(W_dstE in {d_srcA, d_srcB} && W_dstE != RNONE) ||
		(W_dstM in {d_srcA, d_srcB} && W_dstM != RNONE)
	);
#####################################################################
#           modifications for Homework Problem 4.53 end             #
#####################################################################




# Should I stall or inject a bubble into Pipeline Register M?
# At most one of these can be true.
bool M_stall = 0;
# Start injecting bubbles as soon as exception passes through memory stage
bool M_bubble = m_stat in { SADR, SINS, SHLT } || W_stat in { SADR, SINS, SHLT };

# Should I stall or inject a bubble into Pipeline Register W?
bool W_stall = W_stat in { SADR, SINS, SHLT };
bool W_bubble = 0;
#/* $end pipe-all-hcl */
