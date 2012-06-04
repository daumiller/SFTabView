//
//  SFTab.m
//  SFTabView
//
//  Created by Matteo Rattotti on 2/28/10.
//  Copyright 2010 www.shinyfrog.net. All rights reserved.
//  Copyright 2012 Dillon Aumiller. All rights reserved.
//
//==================================================================================================================================
#import "SFTabViewDelegate.h"
#import "SFTab.h"
//----------------------------------------------------------------------------------------------------------------------------------
static CGImageRef activeLeft;
static CGImageRef activeBody;
static CGImageRef activeRight;
static CGImageRef inactiveLeft;
static CGImageRef inactiveBody;
static CGImageRef inactiveRight;
static NSDictionary *textLabelAttributes;

//==================================================================================================================================
#pragma mark -
#pragma mark Tab Header
//==================================================================================================================================
@implementation SFTabHeader
//----------------------------------------------------------------------------------------------------------------------------------
- (BOOL)containsPoint:(CGPoint)p
{
  return FALSE;
}
//----------------------------------------------------------------------------------------------------------------------------------
@end

//==================================================================================================================================
#pragma mark -
#pragma mark Properties
//==================================================================================================================================
@implementation SFTab
//----------------------------------------------------------------------------------------------------------------------------------
@synthesize content;
@synthesize data;
@synthesize selected;
@synthesize width;
@synthesize parent;
//----------------------------------------------------------------------------------------------------------------------------------
- (NSString *)title { return title; }
- (void)setTitle:(NSString *)inTitle
{
  @synchronized(title)
  {
  	[title release];
  	title = [inTitle retain];
  }
  layerLabel.string = title;

  if(parent)
    if(parent.tabAutoSize)
      [parent resizeTabs];
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
- (void)setContent:(id)inContent
{
  if(parent)
  {
	  if(selected && content && parent.target)
	  {
			if(parent.targetIsLayer)
				[content removeFromSuperlayer];
			else
				[content removeFromSuperview];
		}
  }
  
  if(content) [content release];
  content = [inContent retain];
  
  if(parent)
  {
    if(selected && content && parent.target)
    {
      if(parent.targetIsLayer)
        [[parent target] addSublayer:content];
      else
        [[parent target] addSubview:content];
    }
  }
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
- (void)setSelected:(BOOL)inSelected
{
  if(parent && inSelected)
    [parent selectTab:self];
  else
    selected = inSelected;
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
- (void)setWidth:(CGFloat)inWidth
{
  if(inWidth < 60.0) inWidth = 60.0;
  
  if(parent)
    parent.tabWidth = inWidth;
  else
    width = inWidth;
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
- (NSUInteger)index
{
  if(!parent) return 0;
  return [parent indexOfTab:self];
}
- (void)setIndex:(NSUInteger)inIndex
{
  if(!parent) return;
  [parent moveTab:self toIndex:inIndex];
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
- (void)setParent:(SFTabView *)inParent
{
  if(parent)   [parent removeTab:self];
  if(inParent) [inParent addTab:self];
  parent = inParent;
}

//==================================================================================================================================
#pragma mark -
#pragma mark Init, Constructors, & Cleanup
//==================================================================================================================================
+ (void)initialize
{
  [self initStaticHeaderData];
}
//----------------------------------------------------------------------------------------------------------------------------------
+ tab
{
  return [[[SFTab alloc] init] autorelease];
}
//----------------------------------------------------------------------------------------------------------------------------------
+ tabWithTitle:(NSString *)title
{
  return [[[SFTab alloc] initWithTitle:title content:nil data:nil] autorelease];
}
//----------------------------------------------------------------------------------------------------------------------------------
+ tabWithTitle:(NSString *)title content:(id)content
{
  return [[[SFTab alloc] initWithTitle:title content:content data:nil] autorelease];
}
//----------------------------------------------------------------------------------------------------------------------------------
+ tabWithTitle:(NSString *)title content:(id)content data:(id)data;
{
  return [[[SFTab alloc] initWithTitle:title content:content data:data] autorelease];
}
//----------------------------------------------------------------------------------------------------------------------------------
- initWithTitle:(NSString *)inTitle content:(id)inContent data:(id)inData
{
  self = [super init];
  if(self)
  {
    title    = [inTitle retain];
    content  = [inContent retain];
    data     = [inData retain];
    selected = NO;
    width    = 128.0;
    parent   = nil;
    [self initDynamicHeaderData];
  }
  return self;
}
//----------------------------------------------------------------------------------------------------------------------------------
- (void)dealloc
{
  [layerLabel release];
  [layerLeft  release];
  [layerBody  release];
  [layerRight release];
  [title   release];
  [content release];
  [data    release];
  [super dealloc];
}

//==================================================================================================================================
#pragma mark -
#pragma mark Utility
//==================================================================================================================================
- (CGFloat)desiredWidth
{
  if(!title) return 128.0;
  CGFloat actualNeeded = [title sizeWithAttributes:textLabelAttributes].width + 52.0;
  return (actualNeeded > 60.0) ? actualNeeded	: 60.0;
}

//==================================================================================================================================
#pragma mark -
#pragma mark Header Data (class internal)
//==================================================================================================================================
+ (void)initStaticHeaderData
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
- (void)initDynamicHeaderData
{
  NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
  self.frame = CGRectMake(0, 0, width, 28);
  
  layerLabel = [[SFTabHeader layer] retain];
  layerLabel.frame = CGRectMake(25.0, -8.0, width-50.0, 28.0);
  //there's something buggy w/ this -8 (layerLabel.frame.origin.top) adjustment, but i can't find any adverse effects...
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
  layerLabel.string = title;
  
  //for some reason, during dragging these were getting off by 1 pixel
  //so, layerBody is now padded to X:-1 W:+2
  layerLeft  = [[SFTabHeader layer] retain]; layerLeft.frame  = CGRectMake( 0.0, 0.0, 26.0, 28.0);
  layerBody  = [[SFTabHeader layer] retain]; layerBody.frame  = CGRectMake(25.0, 0.0, width-50.0, 28.0);
  layerRight = [[SFTabHeader layer] retain]; layerRight.frame = CGRectMake(width-26.0, 0.0, 26.0, 28.0);
  layerBody.contentsGravity = kCAGravityResize;
  
  [layerLeft  setContents:(id)inactiveLeft];
  [layerBody  setContents:(id)inactiveBody];
  [layerRight setContents:(id)inactiveRight];
  
  [self addSublayer:layerLeft ];
  [self addSublayer:layerBody ]; 
  [self addSublayer:layerRight];
  [self addSublayer:layerLabel];
  [pool drain];
}

//==================================================================================================================================
#pragma mark -
#pragma mark Parent Calls (framework internal)
//==================================================================================================================================
- (void)parentSetParent:(SFTabView *)inParent
{
  if(parent && selected)
    [self parentSetSelected:NO];
  parent = inParent;

  if(parent)
  {
    if(parent.tabAutoSize)
      [parent resizeTabs];
    else
      [self parentSetWidth:parent.tabWidth];
  }
}
//----------------------------------------------------------------------------------------------------------------------------------
- (void)parentSetSelected:(BOOL)inSelected
{
  [CATransaction begin]; 
  [CATransaction setValue:(id)kCFBooleanTrue forKey:kCATransactionDisableActions];
  
  if(inSelected)
  {
    selected = YES;
    [layerLeft  setContents:(id)activeLeft];
    [layerBody  setContents:(id)activeBody];
    [layerRight setContents:(id)activeRight];
    if(content && parent.target)
    {
      if(parent.targetIsLayer)
      {
        [(CALayer *)content setFrame:[parent.target bounds]];
        //TODO: autoresizing for CALayers??
        [parent.target addSublayer:content];
      }
      else
      {
        //casting to avoid multiple definitions warning on setAutoResizingMask:
        [(NSView *)content setFrame:[parent.target bounds]];
        [(NSView *)content setAutoresizingMask: NSViewWidthSizable|NSViewHeightSizable]; //TODO: this should be customizable
        [parent.target addSubview:content];
      }
    }
  }
  else
  {
    selected = NO;
    [layerLeft  setContents:(id)inactiveLeft];
    [layerBody  setContents:(id)inactiveBody];
    [layerRight setContents:(id)inactiveRight];
    if(content && parent.target)
    {
      if(parent.targetIsLayer)
      {
        //VERIFY: removeFromSuperlayer doesn't call autorelease (like removeFromSuperview does)
        //  no mention of it in the docs...
        [content removeFromSuperlayer];
      }
      else
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
- (void)parentSetWidth:(CGFloat)inWidth
{
  width = inWidth;
  layerBody.frame  = CGRectMake(25.0, 0.0, width-50.0, 28.0);
  layerRight.frame = CGRectMake(width-26.0, 0.0, 26.0, 28.0);
  layerLabel.frame = CGRectMake(25.0, -8.0, width-50.0, 28.0);
  //there's something buggy w/ this -8 (layerLabel.frame.origin.top) adjustment, but i can't find any adverse effects...
  if(selected)
    [layerBody setContents:(id)activeBody];
  else
    [layerBody setContents:(id)inactiveBody];
}

@end
