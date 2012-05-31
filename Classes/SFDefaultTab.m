//
//  SFDefaultTab.m
//  tabtest
//
//  Created by Matteo Rattotti on 2/28/10.
//  Copyright 2010 www.shinyfrog.net. All rights reserved.
//  Copyright 2012 Dillon Aumiller. All rights reserved.
//
//==================================================================================================================================
#import "SFDefaultTab.h"
//----------------------------------------------------------------------------------------------------------------------------------
static CGImageRef activeLeft;
static CGImageRef activeBody;
static CGImageRef activeRight;
static CGImageRef inactiveLeft;
static CGImageRef inactiveBody;
static CGImageRef inactiveRight;
static NSDictionary *textLabelAttributes;

//==================================================================================================================================
@implementation SFTabChildLayer
//----------------------------------------------------------------------------------------------------------------------------------
- (BOOL)containsPoint:(CGPoint)p
{
  return FALSE;
}
//----------------------------------------------------------------------------------------------------------------------------------
@end

//==================================================================================================================================
@implementation SFDefaultTab
//----------------------------------------------------------------------------------------------------------------------------------
+ (void)initStaticObjects
{
  NSBundle *myBundle = [NSBundle bundleForClass:[SFTabView class]];
  CFStringRef path; CFURLRef imageURL; CGImageSourceRef imageSource;
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  path  = (CFStringRef)[myBundle pathForResource:@"activeLeft" ofType:@"png"];
  imageURL = CFURLCreateWithFileSystemPath(nil, path, kCFURLPOSIXPathStyle, NO);
  imageSource = CGImageSourceCreateWithURL(imageURL, nil);
  activeLeft = CGImageSourceCreateImageAtIndex(imageSource, 0, nil);
  CFRelease(imageURL); CFRelease(imageSource);
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  path  = (CFStringRef)[myBundle pathForResource:@"activeBody" ofType:@"png"];
  imageURL = CFURLCreateWithFileSystemPath(nil, path, kCFURLPOSIXPathStyle, NO);
  imageSource = CGImageSourceCreateWithURL(imageURL, nil);
  activeBody = CGImageSourceCreateImageAtIndex(imageSource, 0, nil);
  CFRelease(imageURL); CFRelease(imageSource);
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  path  = (CFStringRef)[myBundle pathForResource:@"activeRight" ofType:@"png"];
  imageURL = CFURLCreateWithFileSystemPath(nil, path, kCFURLPOSIXPathStyle, NO);
  imageSource = CGImageSourceCreateWithURL(imageURL, nil);
  activeRight = CGImageSourceCreateImageAtIndex(imageSource, 0, nil);
  CFRelease(imageURL); CFRelease(imageSource);
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  path  = (CFStringRef)[myBundle pathForResource:@"inactiveLeft" ofType:@"png"];
  imageURL = CFURLCreateWithFileSystemPath(nil, path, kCFURLPOSIXPathStyle, NO);
  imageSource = CGImageSourceCreateWithURL(imageURL, nil);
  inactiveLeft = CGImageSourceCreateImageAtIndex(imageSource, 0, nil);
  CFRelease(imageURL); CFRelease(imageSource);
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  path  = (CFStringRef)[myBundle pathForResource:@"inactiveBody" ofType:@"png"];
  imageURL = CFURLCreateWithFileSystemPath(nil, path, kCFURLPOSIXPathStyle, NO);
  imageSource = CGImageSourceCreateWithURL(imageURL, nil);
  inactiveBody = CGImageSourceCreateImageAtIndex(imageSource, 0, nil);
  CFRelease(imageURL); CFRelease(imageSource);
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  path  = (CFStringRef)[myBundle pathForResource:@"inactiveRight" ofType:@"png"];
  imageURL = CFURLCreateWithFileSystemPath(nil, path, kCFURLPOSIXPathStyle, NO);
  imageSource = CGImageSourceCreateWithURL(imageURL, nil);
  inactiveRight = CGImageSourceCreateImageAtIndex(imageSource, 0, nil);
  CFRelease(imageURL); CFRelease(imageSource);
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
  textLabelAttributes = [[NSDictionary dictionaryWithObjectsAndKeys:[NSFont fontWithName:@"LucidaGrande" size:13.0], NSFontAttributeName, nil] retain];
}
//----------------------------------------------------------------------------------------------------------------------------------
- (void)initDynamicObjects:(CGFloat)width;
{
  NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
  self.frame = CGRectMake(0, 0, width, 28);
  
  layerLabel = [[SFTabChildLayer layer] retain];
  layerLabel.frame = CGRectMake(25.0, 0.0, width-50.0, 28.0);
  [layerLabel setFontSize:13.0f];
  [layerLabel setShadowOpacity:.9f];
  layerLabel.shadowOffset    = CGSizeMake(0, -1);
  layerLabel.shadowRadius    = 1.0f;
  layerLabel.shadowColor     = CGColorCreateGenericRGB(1,1,1, 1);
  layerLabel.foregroundColor = CGColorCreateGenericRGB(0.1,0.1,0.1, 1);
  layerLabel.truncationMode  = kCATruncationEnd;
  layerLabel.alignmentMode   = kCAAlignmentCenter;
  CAConstraint *constraint = [CAConstraint constraintWithAttribute: kCAConstraintMidX
                                                        relativeTo: @"superlayer"
                                                         attribute: kCAConstraintMidX];  
  [layerLabel addConstraint:constraint];
  constraint = [CAConstraint constraintWithAttribute: kCAConstraintMidY
                                          relativeTo: @"superlayer"
                                           attribute: kCAConstraintMidY
                                              offset: -2.0];
  [layerLabel addConstraint:constraint];
  constraint = [CAConstraint constraintWithAttribute: kCAConstraintMaxX
                                          relativeTo: @"superlayer"
                                           attribute: kCAConstraintMaxX
                                              offset: -20.0];
  [layerLabel addConstraint:constraint];
  constraint = [CAConstraint constraintWithAttribute: kCAConstraintMinX
                                          relativeTo: @"superlayer"
                                           attribute: kCAConstraintMinX
                                              offset: 20.0];
  [layerLabel addConstraint:constraint];
  [layerLabel setFont:@"LucidaGrande"];
  
  //for some reason, during dragging these were getting off by 1 pixel
  //so, layerBody is now padded to X:25 W:75 (from original X:26 W:73)
  layerLeft  = [[SFTabChildLayer layer] retain]; layerLeft.frame  = CGRectMake( 0.0, 0.0, 26.0, 28.0);
  layerBody  = [[SFTabChildLayer layer] retain]; layerBody.frame  = CGRectMake(25.0, 0.0, width-50.0, 28.0); layerBody.contentsGravity = kCAGravityResize;
  layerRight = [[SFTabChildLayer layer] retain]; layerRight.frame = CGRectMake(width-26.0, 0.0, 26.0, 28.0);
  
  [layerLeft  setContents:(id)inactiveLeft];
  [layerBody  setContents:(id)inactiveBody];
  [layerRight setContents:(id)inactiveRight];
  
  [self addSublayer:layerLeft ];
  [self addSublayer:layerBody ]; 
  [self addSublayer:layerRight];
  [self addSublayer:layerLabel];
  [pool drain];
}
//----------------------------------------------------------------------------------------------------------------------------------
@synthesize representedObject;
- (void)setRepresentedObject:(id)inRepresentedObject
{
  [representedObject release];
  representedObject = [inRepresentedObject retain];
  
  CAConstraintLayoutManager *layout = [CAConstraintLayoutManager layoutManager];
  [self setLayoutManager:layout];
  
  if(!activeLeft) [SFDefaultTab initStaticObjects];
  if(!layerLeft ) [self initDynamicObjects:128.0];
  
  if([representedObject objectForKey:@"name"] != nil)
    layerLabel.string = [representedObject objectForKey:@"name"];
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
- (void)setRepresentedObject:(id)inRepresentedObject andWidth:(CGFloat)width
{
  [representedObject release];
  representedObject = [inRepresentedObject retain];
  
  NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
  CAConstraintLayoutManager *layout = [CAConstraintLayoutManager layoutManager];
  [self setLayoutManager:layout];
  
  if(!activeLeft) [SFDefaultTab initStaticObjects];
  if(!layerLeft ) [self initDynamicObjects:width];
  
  if([representedObject objectForKey:@"name"] != nil)
    layerLabel.string = [representedObject objectForKey:@"name"];
  
  [pool drain];
}

//----------------------------------------------------------------------------------------------------------------------------------
- (void)setSelected:(BOOL)selected
{
  [CATransaction begin]; 
  [CATransaction setValue:(id)kCFBooleanTrue forKey:kCATransactionDisableActions];

  if(selected)
  {
    isActiveTab = YES;
    [layerLeft  setContents:(id)activeLeft];
    [layerBody  setContents:(id)activeBody];
    [layerRight setContents:(id)activeRight];
    //[layerBody addSublayer:layerLabel];
    if(representedObject)
    {
      NSView *container = [representedObject objectForKey:@"container"];
      NSView *content   = [representedObject objectForKey:@"content"  ];
      if(container && content)
      {
        [content   setFrame:[container bounds]];
        [content   setAutoresizingMask:NSViewWidthSizable | NSViewHeightSizable];
        [container addSubview:content];
      }
    }
  }
  else
  {
    isActiveTab = NO;
    [layerLeft  setContents:(id)inactiveLeft];
    [layerBody  setContents:(id)inactiveBody];
    [layerRight setContents:(id)inactiveRight];
    if(representedObject)
    {
      NSView *container = [representedObject objectForKey:@"container"];
      NSView *content   = [representedObject objectForKey:@"content"  ];
      if(container && content)
      {
        NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
        [content retain];
        [content removeFromSuperview];
        [pool drain];
      }
    }
  }
  
  [CATransaction commit];
}
//----------------------------------------------------------------------------------------------------------------------------------
- (CGFloat)desiredWidth
{
  if(!representedObject) return 60.0;
  NSString *name = [representedObject objectForKey:@"name"];
  if(name == nil) return 60.0;
  
  //return [name sizeWithAttributes:textLabelAttributes].width;
  CGFloat desired = [name sizeWithAttributes:textLabelAttributes].width + 52.0;
  return desired;
}
//----------------------------------------------------------------------------------------------------------------------------------
- (void)resize:(CGFloat)width
{
  //parent will ensure width is always >= 60.0
  layerBody.frame  = CGRectMake(25.0, 0.0, width-50.0, 28.0);
  layerRight.frame = CGRectMake(width-26.0, 0.0, 26.0, 28.0);
  layerLabel.frame = layerBody.frame;
  if(isActiveTab)
    [layerBody setContents:(id)activeBody];
  else
    [layerBody setContents:(id)inactiveBody];
}
//----------------------------------------------------------------------------------------------------------------------------------
- (void)dealloc
{
  [representedObject release];
  
  [layerLabel release];
  [layerLeft  release];
  [layerBody  release];
  [layerRight release];
  [super dealloc];
}
//----------------------------------------------------------------------------------------------------------------------------------
@end
