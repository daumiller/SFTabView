//
//  SFDefaultTab.h
//  tabtest
//
//  Created by Matteo Rattotti on 2/28/10.
//  Copyright 2010 www.shinyfrog.net. All rights reserved.
//  Copyright 2012 Dillon Aumiller. All rights reserved.
//
//==================================================================================================================================
#import <Cocoa/Cocoa.h>
#import <QuartzCore/QuartzCore.h>
#import "SFTabView.h"

//==================================================================================================================================
@interface SFTabChildLayer : CATextLayer {}
@end

//==================================================================================================================================
@interface SFDefaultTab : CALayer
{
  id representedObject;
  SFTabChildLayer *layerLeft;
  SFTabChildLayer *layerBody;
  SFTabChildLayer *layerRight;
  SFTabChildLayer *layerLabel;
  BOOL             isActiveTab;
}
@property (retain) id representedObject;
//----------------------------------------------------------------------------------------------------------------------------------
- (void)setRepresentedObject:(id)inRepresentedObject andWidth:(CGFloat)width;
//----------------------------------------------------------------------------------------------------------------------------------
- (void)setSelected:(BOOL)selected;
- (CGFloat)desiredWidth;
- (void)resize:(CGFloat)width;
//==================================================================================================================================
@end
