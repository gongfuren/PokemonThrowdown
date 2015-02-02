//
//  Controller.h
//  PokemonThrowdown
//
//  Created by Ian Cordero on 1/31/15.
//  Copyright (c) 2015 Ian Cordero. All rights reserved.
//

#ifndef __PokemonThrowdown__Controller__
#define __PokemonThrowdown__Controller__

class Window;

//
// Controller
// Every Controller has a reference to window in addition to their respective
// models.
//
class Controller
{
public:
    Controller(Window* window);
    
    ~Controller();
    
    Window* getWindow() const;
        
private:
    Window* window;
};

#endif /* defined(__PokemonThrowdown__Controller__) */
