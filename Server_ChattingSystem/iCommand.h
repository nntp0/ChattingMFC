#pragma once

#ifndef __iCommand_H_INCLUDED__
#define __iCommand_H_INCLUDED__
__interface iCommand {

public:
	virtual void MessageResponse(CString commandResult);
};
#endif