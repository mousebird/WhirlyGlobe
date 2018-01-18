/*
 *  MapboxVectorStyleSymbol.h
 *  WhirlyGlobe-MaplyComponent
 *
 *  Created by Steve Gifford on 2/17/15.
 *  Copyright 2011-2015 mousebird consulting
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

#import "MapboxVectorStyleSet.h"

typedef enum {MBTextCenter,MBTextLeft,MBTextRight,MBTextTop,MBTextBottom,MBTextTopLeft,MBTextTopRight,MBTextBottomLeft,MBTextBottomRight} MapboxTextAnchor;


@interface MapboxVectorSymbolLayout : NSObject

/// @brief Field to use when displaying the text
@property (nonatomic) NSArray<NSString *> *textFields;
/// @brief Font to use for display
@property (nonatomic) NSString *textFontName;
/// @brief The maximum line width for wrapping
@property (nonatomic) double textMaxWidth;
/// If set, the immutable text size
@property (nonatomic) double textSize;
/// If set, a function that controls text size
@property (nonatomic) MaplyVectorFunctionStops *textSizeFunc;
/// How the text is laid out in relation to it's attach point
@property (nonatomic) MapboxTextAnchor textAnchor;

- (instancetype)initWithStyleEntry:(NSDictionary *)styleEntry styleSet:(MaplyMapboxVectorStyleSet *)styleSet viewC:(MaplyBaseViewController *)viewC;

@end

@interface MapboxVectorSymbolPaint : NSObject

// Default text color
@property (nonatomic) UIColor *textColor;
// If there's a halo, this is the color
@property (nonatomic) UIColor *textHaloColor;
// If there's a halo, this is the size
@property (nonatomic) double textHaloWidth;

- (instancetype)initWithStyleEntry:(NSDictionary *)styleEntry styleSet:(MaplyMapboxVectorStyleSet *)styleSet viewC:(MaplyBaseViewController *)viewC;

@end

/// @brief Icons and symbols
@interface MapboxVectorLayerSymbol : MaplyMapboxVectorStyleLayer

@property (nonatomic) MapboxVectorSymbolLayout *layout;
@property (nonatomic) MapboxVectorSymbolPaint *paint;

- (instancetype)initWithStyleEntry:(NSDictionary *)styleEntry parent:(MaplyMapboxVectorStyleLayer *)refLayer styleSet:(MaplyMapboxVectorStyleSet *)styleSet drawPriority:(int)drawPriority viewC:(MaplyBaseViewController *)viewC;

- (NSArray *)buildObjects:(NSArray *)vecObjs forTile:(MaplyTileID)tileID viewC:(MaplyBaseViewController *)viewC;

@end
