//
//  SFTab.h
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
/**
 `SFTab` represents a single tab in a tab view.
 Custom tab types should subclass SFTab.
 */
@interface SFTab : CALayer
{
  NSString *title;
  //NSImage *icon;
  id content;
  id data;
  
  BOOL selected;
  CGFloat width;
  
  SFTabView *parent;
  
  SFTabChildLayer *layerLeft;
  SFTabChildLayer *layerBody;
  SFTabChildLayer *layerRight;
  SFTabChildLayer *layerLabel;
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
/**
 Title of the tab. Displayed in tab header.
 */
@property (retain) NSString *title;
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
/*
 Icon of the tab. Displayed in tab header.
 */
//@property (retain) NSImage *icon;
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
/**
 Tab's content object. Should be either an NSView or CALayer, depending on the `SFTabView` parent's `targetIsLayer` property.
 */
@property (retain) id content;
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
/**
 User data. Store any id here.
 */
@property (retain) id data;
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
/**
 Get or set current tab as selected.
 */
@property (assign) BOOL selected;
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
/**
 Get or set tab width;
 */
@property (assign) CGFloat width;
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
/**
 Get `SFTabView` parent of this tab.
 */
@property (readonly) SFTabView *parent;
//----------------------------------------------------------------------------------------------------------------------------------
/** Constructor. */
+ tab;
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
/**
 Constructor.
 
 @param title Title of tab.
 */
+ tabWithTitle:(NSString *)title;
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
/**
 Constructor.
 
 @param title Title of tab.
 @param content Content of tab (`NSView` or `CALayer`).
 */
+ tabWithTitle:(NSString *)title content:(id)content;
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
/**
 Constructor.
 
 @param title Title of tab.
 @param content Content of tab (`NSView` or `CALayer`).
 @param data User data associated with tab.
 */
+ tabWithTitle:(NSString *)title content:(id)content data:(id)data;
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
/**
 Constructor
 
 @param title Title of tab.
 @param content Content of tab (`NSView` or `CALayer`).
 @param data User data associated with tab.
 */
- initWithTitle:(NSString *)inTitle content:(id)inContent data:(id)inData;
//----------------------------------------------------------------------------------------------------------------------------------
/**
 Get desired width of tab.
 
 Returns the required width to fully display the tab header image, optional title, and optional icon.
 */
- (CGFloat)desiredWidth;
//==================================================================================================================================
@end
