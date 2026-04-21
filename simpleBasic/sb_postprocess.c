#include "include/mySimpleComputer.h"
#include "sb_variables.h"

#define fatal()                                                               \
  if (1)                                                                      \
    {                                                                         \
      fatal = 1;                                                              \
      continue;                                                               \
    }

#define defineVariable(value)                                                 \
  char *comment = variableComments[vap];                                      \
  assemblyProgram[vap].command = &assignmentCommand;                          \
  assemblyProgram[vap].operand = value;                                       \
  assemblyProgram[vap].comment = comment;                                     \
  assemblyProgram[vap].isVariable = 1;

int
sb_postprocess ()
{
  int fatal = 0;

  int constOffset = MEMORY_SIZE - 1 - variablesPoolSize;
  int tempOffset = constOffset - constantsPoolSize;
  int programLimit = tempOffset - maxTempVariablesCount;

  if (ap > programLimit)
    {
      printf ("Error %d: Program is too long / complex.\n", bl);
      printf ("| Memory used by program: %d; Memory used by variables: %d.\n",
              programLimit, MEMORY_SIZE - 1 - programLimit);
      return -1;
    }
  for (int i = 0; i < 26; i++)
    {
      if (definedVariables[i].aDefenitionPos == 0)
        continue;

      int vap = definedVariables[i].aDefenitionPos;
      defineVariable (0);
      assemblyProgram[vap].linkedBasicLine
          = definedVariables[i].bDefenitionPos;
      comment[0] = 'A' + i;
    }

  for (int i = 0; i < constantsPoolSize; i++)
    {
      int vap = constOffset - definedConstants[i].aDefenitionPos;
      defineVariable (atoi (definedConstants[i].value));

      int val = assemblyProgram[vap].operand;
      if (val < 0)
        {
          val = -val;
          val |= (1 << (BITS_PER_COMMAND + BITS_PER_OPERAND));
        }
      assemblyProgram[vap].operand = val;

      assemblyProgram[vap].linkedBasicLine
          = definedVariables[i].bDefenitionPos;
      strcpy (comment, definedConstants[i].value);
    }

  for (int i = 0; i < maxTempVariablesCount; i++)
    {
      int vap = tempOffset - definedConstants[i].aDefenitionPos;
      defineVariable (0);
      assemblyProgram[vap].linkedBasicLine = 0;
      strcpy (comment, "Tmp");
    }

  for (int i = 0; i < ap; i++)
    {
      AssemblyCommand *command = &assemblyProgram[i];
      if (!command->needsFurtherInvestigation)
        continue;

      if (command->command == sc_commands + 10    /*JUMP*/
          || command->command == sc_commands + 11 /*JNEG*/
          || command->command == sc_commands + 12 /*JZ*/
      )
        {
          //   printf ("Jump or Jneg or Jz found\n");
          int ai = 0;
          while (basicProgram[(int)assemblyProgram[ai].linkedBasicLine].line
                 < command->operand)
            ai++;

          if (ai > programLimit)
            {
              printf ("Error at %d: Control point found attempt to jump into "
                      "outbound area.\n",
                      basicProgram[(int)command->linkedBasicLine].line);
              fatal ();
            }

          if (ai == i)
            {
              printf (
                  "Error at %d: Control point found useless infinite loop.\n",
                  basicProgram[(int)command->linkedBasicLine].line);
              fatal ();
            }
          command->operand = ai;
        }

      switch (command->operandType)
        {
        case Constant:
          command->operand = constOffset - command->operand;
          break;
        case Temporary:
          command->operand = tempOffset - command->operand;
          break;
        }

      command->needsFurtherInvestigation = 0;
    }

  if (fatal != 0)
    return -1;

  return 0;
}