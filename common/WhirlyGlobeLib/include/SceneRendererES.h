/*
 *  ESRenderer.h
 *  WhirlyGlobeLib
 *
 *  Created by Steve Gifford on 1/13/11.
 *  Copyright 2011-2017 mousebird consulting
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
 *
 */

#import <QuartzCore/QuartzCore.h>
#import "GLUtils.h"

#import "WhirlyVector.h"
#import "WhirlyKitView.h"
#import "Scene.h"
#import "PerformanceTimer.h"
#import "Lighting.h"

class SceneRendererES;

namespace WhirlyKit
{

/** What and where we're rendering.  This can be a regular framebuffer
 to the screen or to a texture.
 */
class RenderTarget : public Identifiable
{
public:
    RenderTarget();
    RenderTarget(SimpleIdentity newID);
    void init();
    
    // Set up the render target
    bool init(Scene *scene,SimpleIdentity targetTexID);
    
    // Pull in framebuffer info from the current OpenGL State
    bool initFromState(int inWidth,int inHeight);
    
    // Clear up resources from the render target
    void clear();
    
    /// Make this framebuffer active
    void setActiveFramebuffer(SceneRendererES *renderer);
    
    /// Set up the target texture
    void setTargetTexture(Scene *scene,SimpleIdentity newTargetTexID);
    
    /// Set the GL texture directly
    void setTargetTexture(TextureBase *tex);
    
    /// Copy the data out of the destination texture and return it
//    NSData *snapshot();
    
    /// OpenGL ES Name for the frame buffer
    GLuint framebuffer;
    /// OpenGL ES Name for the color buffer
    GLuint colorbuffer;
    /// OpenGL ES Name for the depth buffer
    GLuint depthbuffer;
    /// Output framebuffer size fo glViewport
    int width,height;
    /// Set if we've set up background and suchs
    bool isSetup;
    
    // Clear color, if we're clearing
    GLfloat clearColor[4];
    bool clearEveryFrame;
    // Clear on the next frame, then reset this
    bool clearOnce;
    // Control how the blending into a destination works
    bool blendEnable;
};

// Add a new render target
class AddRenderTargetReq : public ChangeRequest
{
public:
    AddRenderTargetReq(SimpleIdentity renderTargetID,int width,int height,SimpleIdentity texID,bool clearEveryFrame,bool blend,const RGBAColor &clearColor);
    
    /// Add the render target to the renderer
    void execute(Scene *scene,SceneRendererES *renderer,View *view);
    
protected:
    int width,height;
    SimpleIdentity renderTargetID;
    SimpleIdentity texID;
    bool clearEveryFrame;
    RGBAColor clearColor;
    bool blend;
};
    
// Change details about a rendering target.  In this case, just texture.
class ChangeRenderTargetReq : public ChangeRequest
{
public:
    ChangeRenderTargetReq(SimpleIdentity renderTargetID,SimpleIdentity texID);
    
    /// Add the render target to the renderer
    void execute(Scene *scene,SceneRendererES *renderer,View *view);
    
protected:
    SimpleIdentity renderTargetID;
    SimpleIdentity texID;
};
    
// Request a one time clear on the rendering target.  Happens next frame.
class ClearRenderTargetReq : public ChangeRequest
{
public:
    ClearRenderTargetReq(SimpleIdentity renderTargetID);
    
    /// Add the render target to the renderer
    void execute(Scene *scene,SceneRendererES *renderer,View *view);
    
protected:
    SimpleIdentity renderTargetID;
};

// Remove a render target from the rendering loop
class RemRenderTargetReq : public ChangeRequest
{
public:
    RemRenderTargetReq(SimpleIdentity targetID);
    
    /// Remove the render target from the renderer
    void execute(Scene *scene,SceneRendererES *renderer,View *view);
    
protected:
    SimpleIdentity targetID;
};

/** Renderer Frame Info.
 Data about the current frame, passed around by the renderer.
 */
class RendererFrameInfo
{
public:
    RendererFrameInfo();
    RendererFrameInfo(const RendererFrameInfo &that);
    
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW;
    
    /// Renderer version (e.g. OpenGL ES 1 vs 2)
    int glesVersion;
    /// Renderer itself
    WhirlyKit::SceneRendererES *sceneRenderer;
    /// View
    WhirlyKit::View *theView;
    /// Current model matrix from the view
    Eigen::Matrix4f modelTrans,viewTrans;
    Eigen::Matrix4d modelTrans4d,viewTrans4d;
    /// Current projection matrix
    Eigen::Matrix4f projMat;
    Eigen::Matrix4d projMat4d;
    /// What's currently in the GL model matrix.
    /// We combine view and model together
    Eigen::Matrix4f viewAndModelMat;
    Eigen::Matrix4d viewAndModelMat4d;
    /// The model, view, and projection matrix all rolled into one
    Eigen::Matrix4f mvpMat;
    /// Inverse of the model/view/projection matrix
    Eigen::Matrix4f mvpInvMat;
    /// Normal matrix for MVP
    Eigen::Matrix4f mvpNormalMat;
    /// Model, and view matrix but for normal transformation
    Eigen::Matrix4f viewModelNormalMat;
    /// Projection, view, and offset matrices rolled together
    Eigen::Matrix4d pvMat4d;
    Eigen::Matrix4f pvMat;
    /// If the visual view supports wrapping, these are the available offset matrices
    std::vector<Eigen::Matrix4d> offsetMatrices;
    /// Scene itself.  Don't mess with this
    WhirlyKit::Scene *scene;
    /// Expected length of the current frame
    float frameLen;
    /// Time at the start of frame
    TimeInterval currentTime;
    /// Vector pointing up from the globe describing where the view point is
    Eigen::Vector3f eyeVec;
    /// Vector out from the eye point, including tilt
    Eigen::Vector3f fullEyeVec;
    /// Position of user
    Eigen::Vector3d eyePos;
    /// Location of the middle of the screen in display coordinates
    Eigen::Vector3d dispCenter;
    /// Height above surface, if that makes sense
    float heightAboveSurface;
    /// Screen size in display coordinates
    Point2d screenSizeInDisplayCoords;
    /// If using OpenGL ES 2.x, this is the shader
    OpenGLES2Program *program;
    /// Lights, if applicable
    std::vector<DirectionalLight> *lights;
};

/** We support three different ways of using z buffer.  (1) Regular mode where it's on.
    (2) Completely off, priority sorting only.  (3) Priority sorting, but drawables
        are allowed to force the z buffer on temporarily.
  */
typedef enum {zBufferOn,zBufferOff,zBufferOffDefault} WhirlyKitSceneRendererZBufferMode;

/// Base class for the scene renderer.
/// It's subclassed for the specific version of OpenGL ES
class SceneRendererES : public DelayedDeletable
{
public:
    SceneRendererES(int apiVersion);
    virtual ~SceneRendererES();
    
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW;
    
    /// Called right after the constructor
    virtual void setup();
            
    /// Set the render until time.  This is used by things like fade to keep
    ///  the rendering optimization from cutting off animation.
    void setRenderUntil(TimeInterval newTime);
    
    /// A drawable wants continuous rendering (bleah!)
    void addContinuousRenderRequest(SimpleIdentity drawID);
    
    /// Drawable is done with continuous rendering
    void removeContinuousRenderRequest(SimpleIdentity drawID);
    
    /// Call this to force a draw on the next frame.
    /// This turns off the draw optimization, but just for one frame.
    void forceDrawNextFrame();
    
    /// Return true if we have changes to process or display
    virtual bool hasChanges() { return false; }
    
    /// Use this to set the clear color for the screen.  Defaults to black
    void setClearColor(const RGBAColor &color);
    
    /// Return the current clear color
    RGBAColor getClearColor();
    
    /// Get the framebuffer size
    Point2f getFramebufferSize() { return Point2f(framebufferWidth,framebufferHeight); }
    
    /// Return the attached Scene
    Scene *getScene() { return scene; }
    
    /// Return the map view
    View *getView() { return theView; }
    
    /// Return the device scale (e.g. retina vs. not)
    float getScale() { return scale; }
    
    /// Used by the subclasses to determine if the view changed and needs to be updated
    virtual bool viewDidChange();
    
    /// Force a draw at the next opportunity
    virtual void setTriggerDraw();
    
    /// Set the current z buffer mode
    virtual void setZBufferMode(WhirlyKitSceneRendererZBufferMode inZBufferMode) { zBufferMode = inZBufferMode; }
    
    /// Assign a new scene.  Just at startup
    virtual void setScene(WhirlyKit::Scene *newScene);
    
    /// To cull or not to cull (generally not)
    virtual void setDoCulling(bool newCull) { doCulling = newCull; }
    
    /// Set the performance counting interval (0 is off)
    virtual void setPerfInterval(int howLong) { perfInterval = howLong; }
    
    /// If set, we'll use the view changes to trigger rendering
    virtual void setUseViewChanged(bool newVal) { useViewChanged = newVal; }
    
    /// Current view (opengl view) we're tied to
    virtual void setView(WhirlyKit::View *newView) { theView = newView; }
    
    /// If set, we'll draw one more frame than needed after updates stop
    virtual void setExtraFrameMode(bool newMode) { extraFrameMode = newMode; }

    /// Add a render target to start rendering too
    void addRenderTarget(RenderTarget &newTarget);
    
    /// Stop rendering to the matching render target
    void removeRenderTarget(SimpleIdentity targetID);

public:
    // OpenGL Version
    int glesVersion;
    
    /// Scene we're drawing.  This is set from outside
    WhirlyKit::Scene *scene;
    /// The view controls how we're looking at the scene
    WhirlyKit::View *theView;
    /// Set this mode to modify how Z buffering is used (if at all)
    WhirlyKitSceneRendererZBufferMode zBufferMode;
    /// Set this to turn culling on or off.
    /// By default it's on, so leave it alone unless you know you want it off.
    bool doCulling;
    
    /// The pixel width of the CAEAGLLayer.
    GLint framebufferWidth;
    /// The pixel height of the CAEAGLLayer.
    GLint framebufferHeight;
    /// Scale, to reflect the device's screen
    float scale;
    
    /// Statistic: Frames per second
    float framesPerSec;
    /// Statistic: Number of drawables drawn in last frame
    unsigned int numDrawables;
    /// Period over which we measure performance
    int perfInterval;
    
    /// Set if we're using the view based change mechanism to tell when to draw.
    /// This works well for figuring out when the model matrix changes, but
    ///  not so well with animation such as fades, particles systems and such.
    bool useViewChanged;
    /// By default we'll sort all alpha-containing drawables to the end.
    /// Turn this off to tell the renderer you knew what you're doing and
    ///  don't mess with my draw priorities.
    bool sortAlphaToEnd;
    // If this is set, we'll turn off the depth buffering the first time
    //  we hit a drawable with alpha.  Off by default (not surprisingly).
    bool depthBufferOffForAlpha;
    
    /// Force a draw at the next opportunity
    bool triggerDraw;

	unsigned int frameCount;
	TimeInterval frameCountStart;
    WhirlyKit::PerformanceTimer perfTimer;
        
    /// Last time we rendered
    TimeInterval lastDraw;
    
    /// Something wants to make sure we render until at least this point.
    TimeInterval renderUntil;
    
    // The drawables that want continuous rendering on
    WhirlyKit::SimpleIDSet contRenderRequests;
    
    WhirlyKit::RGBAColor clearColor;

    // View state from the last render, for comparison
    Eigen::Matrix4d modelMat,viewMat,projMat;
    
    // If set we draw one extra frame after updates stop
    bool extraFrameMode;
    
    std::vector<RenderTarget> renderTargets;
};

}
