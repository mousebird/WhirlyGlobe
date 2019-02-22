/*
 *  MaplyQuadImageLoader.mm
 *
 *  Created by Steve Gifford on 4/10/18.
 *  Copyright 2012-2018 Saildrone Inc
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

#import "MaplyQuadImageLoader_private.h"
#import "QuadTileBuilder.h"
#import "MaplyImageTile_private.h"
#import "MaplyRenderController_private.h"
#import "MaplyQuadSampler_private.h"
#import "MaplyBaseViewController_private.h"
#import "MaplyRenderTarget_private.h"
#import "MaplyScreenLabel.h"
#import "MaplyRenderTarget_private.h"

using namespace WhirlyKit;

@implementation MaplyImageLoaderReturn

- (void)addImageTile:(MaplyImageTile *)image
{
    loadReturn->images.push_back(image->imageTile);
}

- (void)addImage:(UIImage *)image
{
    ImageTile_iOSRef imageTile = ImageTile_iOSRef(new ImageTile_iOS());
    imageTile->type = MaplyImgTypeImage;
    imageTile->components = 4;
    imageTile->width = -1;
    imageTile->height = -1;
    imageTile->borderSize = 0;
    imageTile->imageStuff = image;
    
    loadReturn->images.push_back(imageTile);
}

- (NSArray<MaplyImageTile *> *)getImages
{
    NSMutableArray *ret = [[NSMutableArray alloc] init];
    for (auto imageTile : loadReturn->images) {
        ImageTile_iOSRef imageTileiOS = std::dynamic_pointer_cast<ImageTile_iOS>(imageTile);
        MaplyImageTile *imgTileObj = [[MaplyImageTile alloc] init];
        imgTileObj->imageTile = imageTileiOS;
        [ret addObject:imgTileObj];
    }
    
    return ret;
}

- (void)addCompObjs:(NSArray<MaplyComponentObject *> *)compObjs
{
    for (MaplyComponentObject *compObj in compObjs)
        loadReturn->compObjs.push_back(compObj->contents);
}

- (NSArray<MaplyComponentObject *> *)getCompObjs
{
    NSMutableArray *ret = [[NSMutableArray alloc] init];
    for (auto compObj : loadReturn->compObjs) {
        MaplyComponentObject *compObjWrap = [[MaplyComponentObject alloc] init];
        compObjWrap->contents = compObj;
        [ret addObject:compObjWrap];
    }
    
    return ret;
}

- (void)addOvlCompObjs:(NSArray<MaplyComponentObject *> *)compObjs
{
    for (MaplyComponentObject *compObj in compObjs)
        loadReturn->ovlCompObjs.push_back(compObj->contents);
}

- (NSArray<MaplyComponentObject *> *)getOvlCompObjs
{
    NSMutableArray *ret = [[NSMutableArray alloc] init];
    for (auto compObj : loadReturn->ovlCompObjs) {
        MaplyComponentObject *compObjWrap = [[MaplyComponentObject alloc] init];
        compObjWrap->contents = compObj;
        [ret addObject:compObjWrap];
    }
    
    return ret;
}

@end

@implementation MaplyImageLoaderInterpreter

- (void)dataForTile:(MaplyImageLoaderReturn *)loadReturn loader:(MaplyQuadLoaderBase *)loader
{
    NSArray *tileDatas = [loadReturn getTileData];
    
    for (NSData *tileData in tileDatas) {
        MaplyImageTile *imageTile = [[MaplyImageTile alloc] initWithPNGorJPEGData:tileData];
        [loadReturn addImageTile:imageTile];
    }
}

@end

@implementation MaplyOvlDebugImageLoaderInterpreter
{
    MaplyBaseViewController * __weak viewC;
    UIFont *font;
}

- (id)initWithViewC:(MaplyBaseViewController *)inViewC
{
    self = [super init];
    viewC = inViewC;
    font = [UIFont systemFontOfSize:12.0];
    
    return self;
}

- (void)dataForTile:(MaplyImageLoaderReturn *)loadReturn loader:(MaplyQuadLoaderBase *)loader
{
    [super dataForTile:loadReturn loader:loader];
    
    MaplyBoundingBox bbox = [loader geoBoundsForTile:loadReturn.tileID];
    MaplyScreenLabel *label = [[MaplyScreenLabel alloc] init];
    MaplyCoordinate center;
    center.x = (bbox.ll.x+bbox.ur.x)/2.0;  center.y = (bbox.ll.y+bbox.ur.y)/2.0;
    label.loc = center;
    label.text = [NSString stringWithFormat:@"%d: (%d,%d)",loadReturn.tileID.level,loadReturn.tileID.x,loadReturn.tileID.y];
    label.layoutImportance = MAXFLOAT;
    
    MaplyComponentObject *labelObj = [viewC addScreenLabels:@[label] desc:
                                      @{kMaplyFont: font,
                                        kMaplyTextColor: UIColor.blackColor,
                                        kMaplyTextOutlineColor: UIColor.whiteColor,
                                        kMaplyTextOutlineSize: @(2.0),
                                        kMaplyEnable: @(false),
                                        }
                                                       mode:MaplyThreadCurrent];
    
    MaplyCoordinate coords[5];
    coords[0] = bbox.ll;  coords[1] = MaplyCoordinateMake(bbox.ur.x, bbox.ll.y);
    coords[2] = bbox.ur;  coords[3] = MaplyCoordinateMake(bbox.ll.x, bbox.ur.y);
    coords[4] = coords[0];
    MaplyVectorObject *vecObj = [[MaplyVectorObject alloc] initWithLineString:coords numCoords:5 attributes:nil];
    [vecObj subdivideToGlobe:0.001];
    MaplyComponentObject *outlineObj = [viewC addVectors:@[vecObj] desc:@{kMaplyEnable: @(false)} mode:MaplyThreadCurrent];
    
    [loadReturn addCompObjs:@[labelObj,outlineObj]];
}

@end

@implementation MaplyDebugImageLoaderInterpreter
{
    MaplyBaseViewController * __weak viewC;
}

- (instancetype)initWithViewC:(MaplyBaseViewController *)inViewC
{
    self = [super init];
    
    viewC = inViewC;
    
    return self;
}

static const int MaxDebugColors = 10;
static const int debugColors[MaxDebugColors] = {0x86812D, 0x5EB9C9, 0x2A7E3E, 0x4F256F, 0xD89CDE, 0x773B28, 0x333D99, 0x862D52, 0xC2C653, 0xB8583D};

- (void)dataForTile:(MaplyImageLoaderReturn *)loadReturn loader:(MaplyQuadLoaderBase *)loader
{
    MaplyTileID tileID = loadReturn.tileID;
    
    CGSize size;  size = CGSizeMake(256,256);
    UIGraphicsBeginImageContext(size);
    
    // Draw into the image context
    int hexColor = debugColors[loadReturn.tileID.level % MaxDebugColors];
    float red = (((hexColor) >> 16) & 0xFF)/255.0;
    float green = (((hexColor) >> 8) & 0xFF)/255.0;
    float blue = (((hexColor) >> 0) & 0xFF)/255.0;
    UIColor *backColor = nil;
    UIColor *fillColor = [UIColor whiteColor];
    backColor = [UIColor colorWithRed:0.0 green:0.0 blue:0.0 alpha:0.7];
    fillColor = [UIColor colorWithRed:red green:green blue:blue alpha:0.7];
    CGContextRef ctx = UIGraphicsGetCurrentContext();
    
    // Draw a rectangle around the edges for testing
    [backColor setFill];
    CGContextFillRect(ctx, CGRectMake(0, 0, size.width, size.height));
    [fillColor setStroke];
    CGContextStrokeRect(ctx, CGRectMake(0, 0, size.width-1, size.height-1));
    
    [fillColor setStroke];
    [fillColor setFill];
    CGContextSetTextDrawingMode(ctx, kCGTextFill);
    NSString *textStr = nil;
    if (loadReturn.frame == -1) {
        textStr = [NSString stringWithFormat:@"%d: (%d,%d)",tileID.level,tileID.x,tileID.y];
    }
    else
        textStr = [NSString stringWithFormat:@"%d: (%d,%d); %d",tileID.level,tileID.x,tileID.y,loadReturn.frame];
    [[UIColor whiteColor] setStroke];
    [[UIColor whiteColor] setFill];
    [textStr drawInRect:CGRectMake(0,0,size.width,size.height) withAttributes:@{NSFontAttributeName:[UIFont systemFontOfSize:24.0]}];
    
    // Grab the image and shut things down
    UIImage *retImage = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    
    [loadReturn addImage:retImage];
}

@end

@implementation MaplyQuadImageLoaderBase

- (instancetype)initWithViewC:(MaplyBaseViewController *)inViewC
{
    self = [super initWithViewC:inViewC];
    
    _zBufferRead = false;
    _zBufferWrite = true;
    _baseDrawPriority = kMaplyImageLayerDrawPriorityDefault;
    _drawPriorityPerLevel = 1;
    _color = [UIColor whiteColor];
    _imageFormat = MaplyImageIntRGBA;
    _borderTexel = 0;
    
    MaplyQuadImageLoaderBase * __weak weakSelf = self;
    
    // Start things out after a delay
    // This lets the caller mess with settings
    dispatch_async(dispatch_get_main_queue(), ^{
        [weakSelf delayedInit];
    });

    return self;
}

- (bool)delayedInit
{
    if (!valid)
        return false;
    
    if (!self.viewC || !self.viewC->renderControl || !self.viewC->renderControl->scene)
        return false;
    
    if (!tileFetcher) {
        tileFetcher = [self.viewC addTileFetcher:MaplyQuadImageLoaderFetcherName];
    }
    loader->tileFetcher = tileFetcher;

    samplingLayer = [self.viewC findSamplingLayer:params forUser:self->loader];
    // Do this again in case they changed them
    loader->setSamplingParams(params);
    loader->setFlipY(self.flipY);
    loader->setBaseDrawPriority(_baseDrawPriority);
    loader->setDrawPriorityPerLevel(_drawPriorityPerLevel);
    
    // Sort out the texture format
    switch (self.imageFormat) {
        case MaplyImageIntRGBA:
        case MaplyImage4Layer8Bit:
        default:
            loader->setTexType(GL_UNSIGNED_BYTE);
            break;
        case MaplyImageUShort565:
            loader->setTexType(GL_UNSIGNED_SHORT_5_6_5);
            break;
        case MaplyImageUShort4444:
            loader->setTexType(GL_UNSIGNED_SHORT_4_4_4_4);
            break;
        case MaplyImageUShort5551:
            loader->setTexType(GL_UNSIGNED_SHORT_5_5_5_1);
            break;
        case MaplyImageUByteRed:
        case MaplyImageUByteGreen:
        case MaplyImageUByteBlue:
        case MaplyImageUByteAlpha:
        case MaplyImageUByteRGB:
            loader->setTexType(GL_ALPHA);
            break;
    }
    
    if (loader->getShaderID() == EmptyIdentity) {
        MaplyShader *theShader = [self.viewC getShaderByName:kMaplyShaderDefaultTriMultiTex];
        if (theShader)
            loader->setShaderID([theShader getShaderID]);
    }
    
    return true;
}

- (void)setShader:(MaplyShader *)shader
{
    if (!loader)
        return;
    
    loader->setShaderID([shader getShaderID]);
}

- (void)setRenderTarget:(MaplyRenderTarget *__nonnull)renderTarget
{
    if (!loader)
        return;
    
    loader->setRenderTarget([renderTarget renderTargetID]);
}

@end

@implementation MaplyQuadImageLoader

- (instancetype)initWithParams:(MaplySamplingParams *)inParams tileInfo:(NSObject<MaplyTileInfoNew> *)tileInfo viewC:(MaplyBaseViewController *)inViewC
{
    if (!inParams.singleLevel) {
        NSLog(@"MaplyQuadImageLoader only supports samplers with singleLevel set to true");
        return nil;
    }
    self = [super initWithViewC:inViewC];
    
    params = inParams->params;
    params.generateGeom = true;
    
    // Loader does all the work.  The Obj-C version is just a wrapper
    self->loader = QuadImageFrameLoader_iosRef(new QuadImageFrameLoader_ios(params,
                                                                            tileInfo,
                                                                            QuadImageFrameLoader::SingleFrame));
    
    self.baseDrawPriority = kMaplyImageLayerDrawPriorityDefault;
    self.drawPriorityPerLevel = 100;
    
    self.flipY = true;
    self.debugMode = false;
    self->minLevel = tileInfo.minZoom;
    self->maxLevel = tileInfo.maxZoom;
    self->valid = true;
    
    return self;
}

- (bool)delayedInit
{
    if (!loadInterp) {
        loadInterp = [[MaplyImageLoaderInterpreter alloc] init];
    }
    loader->layer = self;
    
    if (![super delayedInit])
        return false;
    
    return true;
}

- (MaplyLoaderReturn *)makeLoaderReturn
{
    return [[MaplyImageLoaderReturn alloc] init];
}


// Note: Implement this one
//       Need an array of an array of sources (whee!)

- (instancetype)initWithParams:(MaplySamplingParams *)params tileInfos:(NSArray<NSObject<MaplyTileInfoNew> *> *)tileInfos viewC:(MaplyBaseViewController *)viewC
{
    return nil;
}

@end
