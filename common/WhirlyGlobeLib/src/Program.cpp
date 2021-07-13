/*  Program.cpp
 *  WhirlyGlobeLib
 *
 *  Created by Steve Gifford on 10/23/12.
 *  Copyright 2011-2021 mousebird consulting
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#import "Program.h"
#import "Scene.h"
#import "BasicDrawable.h"

namespace WhirlyKit
{

Program::Program() :
    reduceMode(None),
    changed(true),
    lightsLastUpdated(0)
{
}

const std::string &Program::getName() const
{
    return name;
}

void Program::setReduceMode(ReduceMode inReduceMode)
{
    reduceMode = inReduceMode;
    changed = true;
}

Program::ReduceMode Program::getReduceMode() const
{
    return reduceMode;
}

void Program::setUniBlock(const BasicDrawable::UniformBlock &uniBlock)
{
    changed = true;

    for (auto & ii : uniBlocks)
        if (ii.bufferID == uniBlock.bufferID) {
            ii = uniBlock;
            return;
        }
    
    uniBlocks.push_back(uniBlock);
}

ShaderAddTextureReq::ShaderAddTextureReq(SimpleIdentity shaderID,SimpleIdentity nameID,SimpleIdentity texID,int textureSlot)
: shaderID(shaderID), nameID(nameID), texID(texID), textureSlot(textureSlot)
{
}

void ShaderAddTextureReq::execute(Scene *scene, SceneRenderer *renderer, View *view)
{
    Program *prog = scene->getProgram(shaderID);
    TextureBaseRef tex = scene->getTexture(texID);
    if (prog && tex)
    {
        prog->setTexture(nameID,tex.get(),textureSlot);
    }
}

ShaderRemTextureReq::ShaderRemTextureReq(SimpleIdentity shaderID,SimpleIdentity texID)
: shaderID(shaderID), texID(texID)
{
}

void ShaderRemTextureReq::execute(Scene *scene,SceneRenderer *renderer,WhirlyKit::View *view)
{
    Program *prog = scene->getProgram(shaderID);
    if (prog)
        prog->clearTexture(texID);
}

ProgramUniformBlockSetRequest::ProgramUniformBlockSetRequest(SimpleIdentity inProgID,const RawDataRef &uniData,int bufferID)
{
    progID = inProgID;
    uniBlock.blockData = uniData;
    uniBlock.bufferID = bufferID;
}

void ProgramUniformBlockSetRequest::execute(Scene *scene,SceneRenderer *renderer,View *view)
{
    Program *prog = scene->getProgram(progID);
    if (prog) {
        prog->setUniBlock(uniBlock);
    }
}

}
