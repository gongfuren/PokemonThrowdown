//
//  Shader.fsh
//  PokemonThrowdown
//
//  Created by Ian Cordero on 6/9/14.
//  Copyright (c) 2014 Ian Cordero. All rights reserved.
//

varying lowp vec4 colorVarying;

void main()
{
    gl_FragColor = colorVarying;
}
