//
//  SFTab.h
//  SFTabView
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
//simple CALayer child class that will always return false to containsPoint:
@interface SFTabHeader : CATextLayer {}
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
  
  BOOL    selected;
  CGFloat width;
  
  SFTabView *parent;
  
  SFTabHeader *layerLeft;
  SFTabHeader *layerBody;
  SFTabHeader *layerRight;
  SFTabHeader *layerLabel;
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
/**
 Title of the tab. Displayed in tab header.
 */
@property (nonatomic, retain) NSString *title;
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
/*
 Icon of the tab. Displayed in tab header.
 */
//@property (retain) NSImage *icon;
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
/**
 Tab's content object. Should be either an NSView or CALayer, depending on the `SFTabView` parent's `targetIsLayer` property.
 */
@property (nonatomic, retain) id content;
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
/**
 User data. Store any id here.
 */
@property (nonatomic, retain) id data;
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
/**
 Get or set current tab as selected.
 
 + Setting this value will bypass `SFTabView` parent's delegate's `shouldSelectTab:` method.
 + The only valid value to assign to this property is `YES`.
 */
@property (nonatomic, assign) BOOL selected;
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
/**
 Get or set tab width.
 
 + There is currently a hard-coded minimum value of 60.
 + If this value is directly set, all sibling tabs will also resize to the given width.
 + Assigning has no effect when parent's `tabAutoSize` is set to `YES`.
 */
@property (nonatomic, assign) CGFloat width;
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
/**
 Tab's index within parent SFTabView.
 */
@property (nonatomic, assign) NSUInteger index;
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
/**
 Get or set `SFTabView` parent of this tab.
 */
@property (nonatomic, assign) SFTabView *parent;
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
 **Note:** Currently will never return less than the hard-coded minimum value of 60.
 */
- (CGFloat)desiredWidth;
//==================================================================================================================================

- (void)test;

//These should only be called by our SFTabView parent.
- (void)parentSetParent:(SFTabView *)inParent;
- (void)parentSetSelected:(BOOL)selected;
- (void)parentSetWidth:(CGFloat)width;
@end
