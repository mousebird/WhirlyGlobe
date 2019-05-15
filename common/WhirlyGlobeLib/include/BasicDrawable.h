/*
 *  BasicDrawable.h
 *  WhirlyGlobeLib
 *
 *  Created by Steve Gifford on 2/1/11.
 *  Copyright 2011-2019 mousebird consulting
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

#import <vector>
#import <set>
#import <map>
#import "Identifiable.h"
#import "WhirlyVector.h"
#import "GlobeView.h"
#import "Drawable.h"
#import "VertexAttribute.h"

namespace WhirlyKit
{

typedef enum {Points,Lines,Triangles} GeometryType;

/** The Basic Drawable is the one we use the most.  It's
    a general purpose container for static geometry which
    may or may not be textured.
    These are generated by the BasicDrawableBuilder and any
    set calls indicate that value can be changed during run-time.
    The get calls are used by the renderer for state to be set up
    outside this drawable.
 */
class BasicDrawable : public Drawable
{
friend class BasicDrawableInstance;
friend class BasicDrawableInstanceBuilder;
friend class BasicDrawableBuilder;

public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW;

    /// Simple triangle.  Can obviously only have 2^16 vertices
    class Triangle
    {
    public:
        Triangle();
        /// Construct with vertex IDs
        Triangle(unsigned short v0,unsigned short v1,unsigned short v2);
        unsigned short verts[3];
    };

    /// Construct empty
    BasicDrawable(const std::string &name);
    virtual ~BasicDrawable();
    
    /// We're allowed to turn drawables off completely
    virtual bool isOn(RendererFrameInfo *frameInfo) const;
    /// True to turn it on, false to turn it off
    void setOnOff(bool onOff);
    
    /// Return true if the shader is animating for this type of drawable
    virtual bool hasMotion() const;

    /// Return the local MBR, if we're working in a non-geo coordinate system
    virtual Mbr getLocalMbr() const;

    /// Return the Matrix if there is an active one (ideally not)
    virtual const Eigen::Matrix4d *getMatrix() const;

    /// Return true if the drawable has alpha.  These will be sorted last.
    virtual bool hasAlpha(RendererFrameInfo *frameInfo) const;

    /// Set the time range for enable
    void setEnableTimeRange(TimeInterval inStartEnable,TimeInterval inEndEnable);

    /// Set the fade in and out
    virtual void setFade(TimeInterval inFadeDown,TimeInterval inFadeUp);
    
    /// Set the viewer based visibility
    virtual void setViewerVisibility(double minViewerDist,double maxViewerDist,const Point3d &viewerCenter);

    /// Set what range we can see this drawable within.
    /// The units are in distance from the center of the globe and
    ///  the surface of the globe as at 1.0
    virtual void setVisibleRange(float minVis,float maxVis,float minVisBand=0.0,float maxVisBand=0.0);
    
    /// We use this to sort drawables
    virtual unsigned int getDrawPriority() const;

    /// Draw priority used for sorting
    virtual void setDrawPriority(unsigned int newPriority);
    
    /// Set the active transform matrix
    virtual void setMatrix(const Eigen::Matrix4d *inMat);
    
    /// Check if the force Z buffer on mode is on
    virtual bool getRequestZBuffer() const;
    virtual void setRequestZBuffer(bool val);
    
    /// Set the z buffer mode for this drawable
    virtual bool getWriteZbuffer() const;
    virtual void setWriteZBuffer(bool val);

    /// Drawables can override where they're drawn.  EmptyIdentity is the regular screen.
    virtual SimpleIdentity getRenderTarget() const;
    
    // If set, we'll render this data where directed
    void setRenderTarget(SimpleIdentity newRenderTarget);
    
    /// Set the line width (if using lines)
    virtual void setLineWidth(float inWidth);

    /// Used to override a color that's already been built in (by changeVector:)
    virtual void setOverrideColor(RGBAColor inColor);
    virtual void setOverrideColor(unsigned char inColor[]);

    /// Texture ID and pointer to vertex attribute info
    class TexInfo
    {
    public:
        TexInfo() : texId(EmptyIdentity), texCoordEntry(0),
        relLevel(0), relX(0), relY(0),
        size(0), borderTexel(0) { }
        /// Texture ID within the scene
        SimpleIdentity texId;
        /// Vertex attribute entry for this set of texture coordinates
        int texCoordEntry;
        /// Our use of this texture relative to its native resolution
        int relLevel,relX,relY;
        /// Size of a texture side
        int size;
        /// Border texels to avoid.  Used for blending.
        int borderTexel;
    };
    
    /// Return the current texture info
    virtual const std::vector<TexInfo> &getTexInfo();
    
    /// Set the texture ID for a specific slot.  You get this from the Texture object.
    virtual void setTexId(unsigned int which,SimpleIdentity inId);
    
    /// Set all the textures at once
    virtual void setTexIDs(const std::vector<SimpleIdentity> &texIDs);
    
    /// Set the relative offsets for texture usage.
    /// We use these to look up parts of a texture at a higher level
    virtual void setTexRelative(int which,int size,int borderTexel,int relLevel,int relX,int relY);
    
    /// Change all the uniforms applied at once
    virtual void setUniforms(const SingleVertexAttributeSet &newUniforms);
    
    /// Add a tweaker to be run before each frame
    virtual void addTweaker(DrawableTweakerRef tweak);

    /// Update anything associated with the renderer.  Probably renderUntil.
    virtual void updateRenderer(SceneRenderer *renderer);
        
    /// If present, we'll do a pre-render calculation pass with this program set
    virtual SimpleIdentity getCalculationProgram() const;
    
    /// Some drawables have a pre-render phase that uses the GPU for calculation
    virtual void calculate(RendererFrameInfo *frameInfo,Scene *scene);
    
    /// For OpenGLES2, this is the program to use to render this drawable.
    virtual SimpleIdentity getProgram() const;
    void setProgram(SimpleIdentity progId);

    /// Set up what you need in the way of context and draw.
    virtual void draw(RendererFrameInfo *frameInfo,Scene *scene) = 0;
    
public:
    GeometryType type;
    bool on;  // If set, draw.  If not, not
    TimeInterval startEnable,endEnable;
    TimeInterval fadeUp,fadeDown;  // Controls fade in and fade out
    float minVisible,maxVisible;
    float minVisibleFadeBand,maxVisibleFadeBand;
    double minViewerDist,maxViewerDist;
    Point3d viewerCenter;
    unsigned int drawPriority;  // Used to sort drawables
    float drawOffset;    // Number of units of Z buffer resolution to offset upward (by the normal)
    bool isAlpha;  // Set if we want to be drawn last
    bool motion;   // If set, this need continuous render
    
    SimpleIdentity programId;    // Program to use for rendering
    SimpleIdentity renderTargetID;
    Mbr localMbr;  // Extents in a local space, if we're not using lat/lon/radius
    std::vector<TexInfo> texInfo;
    float lineWidth;
    // For zBufferOffDefault mode we'll sort this to the end
    bool requestZBuffer;
    // When this is set we'll update the z buffer with our geometry.
    bool writeZBuffer;

    bool hasMatrix;
    // If the drawable has a matrix, we'll transform by that before drawing
    Eigen::Matrix4d mat;

    // Attributes associated with each vertex, some standard some not
    std::vector<VertexAttribute *> vertexAttributes;
    // Entries for the standard attributes we create on startup
    int colorEntry,normalEntry;

    // We'll nuke the data arrays when we hand over the data to GL
    unsigned int numPoints, numTris;
    RGBAColor color;
    bool hasOverrideColor;  // If set, we've changed the default color

    // Uniforms to apply to shader
    SingleVertexAttributeSet uniforms;
        
    // If set the geometry is already in OpenGL clip coordinates, so no transform
    bool clipCoords;
};

/** Drawable Tweaker that cycles through textures.
 Looks at the current time and decides which two textures to use.
 */
class BasicDrawableTexTweaker : public DrawableTweaker
{
public:
    BasicDrawableTexTweaker(const std::vector<SimpleIdentity> &texIDs,TimeInterval startTime,double period);
    
    /// Modify the active texture IDs
    void tweakForFrame(Drawable *draw,RendererFrameInfo *frame);
protected:
    std::vector<SimpleIdentity> texIDs;
    TimeInterval startTime;
    double period;
};

/** Calculates important values for the screen space texture application and
    sets the results in the shader.
  */
class BasicDrawableScreenTexTweaker : public DrawableTweaker
{
public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW;

    BasicDrawableScreenTexTweaker(const Point3d &centerPt,const Point2d &texScale);
    
    /// Modify the active shader
    void tweakForFrame(Drawable *draw,RendererFrameInfo *frame);
protected:
    Point3d centerPt;
    Point2d texScale;
};

/// Reference counted version of BasicDrawable
typedef std::shared_ptr<BasicDrawable> BasicDrawableRef;

/// Ask the renderer to change a drawable's color
class ColorChangeRequest : public DrawableChangeRequest
{
public:
    ColorChangeRequest(SimpleIdentity drawId,RGBAColor color);
    
    void execute2(Scene *scene,SceneRenderer *renderer,DrawableRef draw);
    
protected:
    unsigned char color[4];
};

/// Turn a given drawable on or off.  This doesn't delete it.
class OnOffChangeRequest : public DrawableChangeRequest
{
public:
    OnOffChangeRequest(SimpleIdentity drawId,bool OnOff);
    
    void execute2(Scene *scene,SceneRenderer *renderer,DrawableRef draw);
    
protected:
    bool newOnOff;
};

/// Change the visibility distances for the given drawable
class VisibilityChangeRequest : public DrawableChangeRequest
{
public:
    VisibilityChangeRequest(SimpleIdentity drawId,float minVis,float maxVis);
    
    void execute2(Scene *scene,SceneRenderer *renderer,DrawableRef draw);
    
protected:
    float minVis,maxVis;
};

/// Change the fade times for a given drawable
class FadeChangeRequest : public DrawableChangeRequest
{
public:
    FadeChangeRequest(SimpleIdentity drawId,TimeInterval fadeUp,TimeInterval fadeDown);
    
    void execute2(Scene *scene,SceneRenderer *renderer,DrawableRef draw);
    
protected:
    TimeInterval fadeUp,fadeDown;
};

/// Change the texture used by a drawable
class DrawTexChangeRequest : public DrawableChangeRequest
{
public:
    DrawTexChangeRequest(SimpleIdentity drawId,unsigned int which,SimpleIdentity newTexId);
    DrawTexChangeRequest(SimpleIdentity drawId,unsigned int which,SimpleIdentity newTexId,int size,int borderTexel,int relLevel,int relX,int relY);
    
    void execute2(Scene *scene,SceneRenderer *renderer,DrawableRef draw);
    
protected:
    unsigned int which;
    SimpleIdentity newTexId;
    bool relSet;
    int size,borderTexel;
    int relLevel,relX,relY;
};

/// Change the textures used by a drawable
class DrawTexturesChangeRequest : public DrawableChangeRequest
{
public:
    DrawTexturesChangeRequest(SimpleIdentity drawId,const std::vector<SimpleIdentity> &newTexIDs);
    
    void execute2(Scene *scene,SceneRenderer *renderer,DrawableRef draw);
    
protected:
    const std::vector<SimpleIdentity> newTexIDs;
};

/// Change the transform matrix on a drawable
class TransformChangeRequest : public DrawableChangeRequest
{
public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW;

    TransformChangeRequest(SimpleIdentity drawId,const Eigen::Matrix4d *newMat);
    
    void execute2(Scene *scene,SceneRenderer *renderer,DrawableRef draw);
    
protected:
    Eigen::Matrix4d newMat;
};

/// Change the drawPriority on a drawable
class DrawPriorityChangeRequest : public DrawableChangeRequest
{
public:
    DrawPriorityChangeRequest(SimpleIdentity drawId,int drawPriority);
    
    void execute2(Scene *scene,SceneRenderer *renderer,DrawableRef draw);
    
protected:
    int drawPriority;
};

/// Change the line width on a drawable
class LineWidthChangeRequest : public DrawableChangeRequest
{
public:
    LineWidthChangeRequest(SimpleIdentity drawId,float lineWidth);
    
    void execute2(Scene *scene,SceneRenderer *renderer,DrawableRef draw);
    
protected:
    float lineWidth;
};
    
/// Reset the uniforms passed into a shader for a specific drawable
class DrawUniformsChangeRequest : public DrawableChangeRequest
{
public:
    DrawUniformsChangeRequest(SimpleIdentity drawID,const SingleVertexAttributeSet &attrs);
    
    void execute2(Scene *scene,SceneRenderer *renderer,DrawableRef draw);
    
protected:
    SingleVertexAttributeSet attrs;
};

/// Change the render target (or clear it)
class RenderTargetChangeRequest : public DrawableChangeRequest
{
public:
    RenderTargetChangeRequest(SimpleIdentity drawId,SimpleIdentity );
    
    void execute2(Scene *scene,SceneRenderer *renderer,DrawableRef draw);
    
protected:
    SimpleIdentity targetID;
};
    
}
