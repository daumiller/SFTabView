//
//  SFTabView.h
//  SFTabView
//
//  Created by Matteo Rattotti on 2/27/10.
//  Copyright 2010 www.shinyfrog.net. All rights reserved.
//  Copyright 2012 Dillon Aumiller. All rights reserved.
//
//==================================================================================================================================
#import <Cocoa/Cocoa.h>
#import <QuartzCore/QuartzCore.h>
//==================================================================================================================================
@protocol SFTabViewDelegate;

/**
 An SFTabView provides a convenient way to manage tabs in your application. 
 The view contains a row of tabs that can be selected one at time and reordered by dragging.
 
 The SFTabViewAppDelegate protocol will notify the delegate during notable Tab View events, 
 like selecting, adding and deleting tabs.
 
 The tabs are rendered using a CALayer subclass, the Tab View will know which class to use by
 setting the defaultTabClassName property.
  
*/

@interface SFTabView : NSView
{
  IBOutlet NSObject  <SFTabViewDelegate> *delegate;

  CALayer *currentClickedTab;
  CALayer *currentSelectedTab;

  CALayer *tabsLayer;
  CAScrollLayer *scrollLayer;

  NSMutableArray *arrangedTabs;
  NSPoint mouseDownPoint, mouseDownStartingPoint;

  NSString *defaultTabClassName;

  BOOL canDragTab;

  int tabOffset;
  int startingOffset;
  int tabMagneticForce;
  
  BOOL tabAutoSize;
  CGFloat tabWidth, tabMinWidth, tabMaxWidth;
}

//////////////////////////////////////////////////////////////////////////////////////////
/// @name Properties
//////////////////////////////////////////////////////////////////////////////////////////


/** 
  The SFTabView Delegate.
 
 */
@property (retain) id delegate;


/** 
  The CALayer subclass that will render a single tab.
 
 This class should be conform to the SFTab protocoll.  
 */
@property (retain) NSString *defaultTabClassName;


/** 
  The space between two tabs.

 This property can hold negative values in order to make tabs overlap. 
 
 This property should be only changed when the Tab Bar contain no tabs.
 */
@property int tabOffset;


/** 
  The space before the first tab.
 
 The first tab will appear shifted to "startingOffset" pixel.
 
 This property should be only changed when the Tab Bar contain no tabs.

 */
@property int startingOffset;


/** 
  The number of pixel that the user need to drag before the tab actually move.
 
 High value will make the tabs harder to move, a value of 0 will make the tab moving at
 every drag tentative.
 */
@property int tabMagneticForce;

/**
  Determines if tabs will grow/shrink as needed.
 
 When YES, tabs will attempt to fit name labels' text.
 */
@property (nonatomic, assign) BOOL tabAutoSize;

/**
  Size of fixed-width tabs.
 
 Only used when (tabAutoSize == NO).
 Note this currently has a hard-coded minimum value of 60.0.
 */
@property (nonatomic, assign) CGFloat tabWidth;

/**
  Minimum width of tabs.
 
 Note this currently has a hard-coded minimum value of 60.0.
 */
@property (nonatomic, assign) CGFloat tabMinWidth;

/**
  Maximum width of tabs.
 
 Note this currently has a card-coded minimum value of 60.0
 */
@property (nonatomic, assign) CGFloat tabMaxWidth;

//////////////////////////////////////////////////////////////////////////////////////////
/// @name Adding and Removing Tabs
//////////////////////////////////////////////////////////////////////////////////////////


#pragma mark -
#pragma mark Adding and Removing Tabs

/** 
  Add a new tab to the tabview, using the representedObject as model.
  
 @param representedObject An object passed to the CALayer subclass that contain all the in
 fomation needed for rendering the tab.
 @see addTabAtIndex:withRepresentedObject:
 
 */
- (void) addTabWithRepresentedObject: (id) representedObject;


/** 
  Add a new tab to the tabview at the specified index, using the representedObject as model.
 
 @param index The index in the tabview at which to insert a new tab.
 @param representedObject An object passed to the CALayer subclass that contain all the in
 fomation needed for rendering the tab.
 @see addTabWithRepresentedObject:
 
 */
- (void) addTabAtIndex: (int) index withRepresentedObject: (id) representedObject;


/** 
  Remove the tab from the tabview.
 
 @param tab The tab to remove from the tabview.
 @see removeTabAtIndex:
 
 */
- (void) removeTab: (CALayer *) tab;


/** 
  Remove the tab at index.
 
 @param index The index from which to remove the object in the tabview.
 @see removeTab:
 
 */
- (void) removeTabAtIndex: (int) index;


//////////////////////////////////////////////////////////////////////////////////////////
/// @name Accessing Tabs
//////////////////////////////////////////////////////////////////////////////////////////


#pragma mark -
#pragma mark Accessing Tabs


/** 
  Returns the index corresponding to tab.
 
 Tabs are considered equal if isEqual: returns YES.
 
 @param tab A tab contained in the Tab View.
 @return The index whose corresponding tab object is equal to tab. If none of the objects in the tabview is equal to tab, returns NSNotFound.
 */
- (int) indexOfTab: (CALayer *) tab;


/** 
  Returns the number of tab in the Tab View.
 */
- (int) numberOfTabs;


/**
  Returns the tab located at index.
 
 If index is beyond the end of the Tab View (that is, if index is greater than or equal to the value returned by numberOfTabs), an NSRangeException is raised.
 
 @param index An index within the bounds of the Tab View.
 @return The tab located at index.
 @see numberOfTabs
 */
- (CALayer *) tabAtIndex: (int) index;


/** 
  Returns an array contaning all the Tab View tabs.
 @return An array contaning all the Tab View tabs.
 */
- (NSArray *) arrangedTabs;


/** 
  Returns the first tab in the Tab View.
 @return The first tab in the Tab View. If the Tab View contain no tabs, returns nil.
 */
- (CALayer *) firstTab;


/** 
  Returns the last tab in the Tab View.
 @return The last tab in the Tab View. If the Tab View contain no tabs, returns nil.
 */
- (CALayer *) lastTab;


//////////////////////////////////////////////////////////////////////////////////////////
/// @name Selecting Tabs
//////////////////////////////////////////////////////////////////////////////////////////


#pragma mark -
#pragma mark Selecting a Tab


/** 
  Select the given tab in the tabview.
 @param tab A tab contained in the Tab View.
 @see selectFirstTab:
 @see selectLastTab:
 @see selectNextTab:
 @see selectPreviousTab:
 */
- (void) selectTab: (CALayer *) tab;


/** 
  Select a tab at given index.
 @param index An index within the bounds of the Tab View.

 @see selectFirstTab:
 @see selectLastTab:
 @see selectNextTab:
 @see selectPreviousTab: 
 */
- (void) selectTabAtIndex: (unsigned int) index;


/** 
  Select the first tab of the Tab View.
 @param sender Typically the object that sent the message.
 
 @see selectFirstTab:
 @see selectLastTab:
 @see selectNextTab:
 @see selectPreviousTab: 
 */
- (void) selectFirstTab: (id) sender;


/** 
  Select the last tab of the Tab View
 @param sender Typically the object that sent the message.
 
 @see selectFirstTab:
 @see selectLastTab:
 @see selectNextTab:
 @see selectPreviousTab: 
 */
- (void) selectLastTab: (id) sender;


/** 
  Select the tab on the right of the current selected tab.
 
 If the tab is the last one, the first tab of the Tab View will be selected, and
 the Tab View will be scrolled according.
 
 @param sender Typically the object that sent the message.
 
 @see selectFirstTab:
 @see selectLastTab:
 @see selectNextTab:
 @see selectPreviousTab: 
 */
- (void) selectNextTab: (id) sender;


/** 
  Select the tab on the left of the current selected tab.
 
 If the tab is the first one, the last tab of the Tab View will be selected, and
 the Tab View will be scrolled according.
 
 @param sender Typically the object that sent the message.
 
 @see selectFirstTab:
 @see selectLastTab:
 @see selectNextTab:
 @see selectPreviousTab: 
 */
- (void) selectPreviousTab: (id) sender;


/** 
  Returns the current selected tab.
 @return The current selected tab in the Tab View. If the Tab View contain no tabs, returns nil.
 */
- (CALayer *) selectedTab;

//////////////////////////////////////////////////////////////////////////////////////////
/// @name Scrolling
//////////////////////////////////////////////////////////////////////////////////////////


#pragma mark -
#pragma mark Scrolling


/** 
  Scroll the Tab View until tab is fully visibile.
 @param tab A tab contained in the Tab View.
 
 This method will scroll the Tab View using the default animation.
 
 @see scrollToTab:animated:
 */
- (void) scrollToTab: (CALayer *) tab;


/** 
  Scroll the Tab View until tab is fully visibile.
 @param tab A tab contained in the Tab View.
 @param animated Specify YES to animate the transition or NO if you do not want the transition to be animated.
 
 @see scrollToTab:
 */
- (void) scrollToTab: (CALayer *) tab animated: (BOOL) animated;
- (void) scrollToPoint: (CGPoint) point animated: (BOOL) animated;

@end

#pragma mark -
#pragma mark Private Methods

@interface SFTabView (Private)

- (CALayer *) tabsLayer;
- (CAScrollLayer *) scrollLayer;

- (void) setupObservers;
- (void) setDefaults;
- (void) adjustTabLayerScrollAnimated: (BOOL) animated;
- (void) rearrangeInitialTab: (CALayer *) initialTab toLandingTab:(CALayer *) landingTab withCurrentPoint: (CGPoint) currentPoint direction: (BOOL) direction;

- (NSArray *) tabSequenceForStartingTabIndex: (int) startingIndex endingTabIndex: (int) endingIndex direction: (BOOL) direction;
- (int) startingXOriginForTabAtIndex: (int) index;
- (CABasicAnimation *) tabMovingAnimation;
- (NSPoint) deltaFromStartingPoint:(NSPoint)startingPoint endPoint:(NSPoint) endPoint;

@end

