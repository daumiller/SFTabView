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
@class SFTab;

/**
 An SFTabView provides a convenient way to manage tabs in your application. 
 The view contains a row of tabs that can be selected one at time and reordered by dragging.
 
 The SFTabViewAppDelegate protocol will notify the delegate during notable Tab View events, 
 like selecting, adding and deleting tabs.
 
 Custom SFTab subclassed tabs can be used by setting the `defaultTabClassName` property.
*/

@interface SFTabView : NSView
{
  IBOutlet NSObject  <SFTabViewDelegate> *delegate;

  id currentClickedTab;
  id currentSelectedTab;

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
  
  id target;
  BOOL targetIsLayer;
}

//----------------------------------------
/** @name Properties */
//----------------------------------------
/** 
  The SFTabView Delegate.
 
 */
@property (retain) id delegate;

/** 
  The SFTab subclass that will represent a single tab.
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
 
 + When `tabAutoSize` is YES, this is a read-only value.
 + This currently has a hard-coded minimum value of 60.0.
 */
@property (nonatomic, assign) CGFloat tabWidth;

/**
  Minimum width of tabs.
 
 Note: this currently has a hard-coded minimum value of 60.0.
 */
@property (nonatomic, assign) CGFloat tabMinWidth;

/**
  Maximum width of tabs.
 
 Note: this currently has a card-coded minimum value of 60.0
 */
@property (nonatomic, assign) CGFloat tabMaxWidth;

/**
  Target view/layer to receive Tab content.
 
 If `target` is set, and the selected tab has set `content`, its content will be set as the target's current subview or sublayer.
 */
@property (nonatomic, assign) id target;

/**
 If YES, `target` is assumed to be a `CALayer`; if NO, an `NSView`.
 */
@property (nonatomic, assign) BOOL targetIsLayer;

#pragma mark -
#pragma mark Adding and Removing Tabs
//----------------------------------------
/** @name Adding and Removing Tabs */
//----------------------------------------

/**
 Add an existing SFTab to the view.
 
 @param tab Existing tab to add.
 */
- (void) addTab:(id)tab;

/**
 Add a new tab.
 
 + `title` will be `@"New Tab"`
 + `content` will be `nil`
 + `data` will be `nil`
 */
- (id) addNewTab;

/**
 Add a new tab.
 
 + `content` will be `nil`
 + `data` will be `nil`
 
 @param title Title of new tab.
 */
- (id) addNewTabWithTitle:(NSString *)title;

/**
 Add a new tab.
 
 + `data` will be `nil`
 
 @param title Title of new tab.
 @param content Content view/layer of new tab.
 */
- (id) addNewTabWithTitle:(NSString *)title content:(id)content;

/**
 Add a new tab.
 
 @param title Title of new tab.
 @param content Content view/layer of new tab.
 @param data User data for new tab.
 */
- (id) addNewTabWithTitle:(NSString *)title content:(id)content data:(id)data;

/** 
  Remove the tab from the tabview.
 
 @param tab The tab to remove from the tabview.
 @see removeTabAtIndex:
 
 */
- (void) removeTab: (id) tab;


/** 
  Remove the tab at index.
 
 @param index The index from which to remove the object in the tabview.
 @see removeTab:
 
 */
- (void) removeTabAtIndex: (int) index;

#pragma mark -
#pragma mark Accessing Tabs
//----------------------------------------
/** @name Accessing Tabs */
//----------------------------------------

/** 
  Returns the index corresponding to tab.
 
 Tabs are considered equal if isEqual: returns YES.
 
 @param tab A tab contained in the Tab View.
 @return The index whose corresponding tab object is equal to tab. If none of the objects in the tabview is equal to tab, returns NSNotFound.
 */
- (int) indexOfTab: (id) tab;


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
- (id) tabAtIndex: (int) index;


/** 
  Returns an array contaning all the Tab View tabs.
 @return An array contaning all the Tab View tabs.
 */
- (NSArray *) arrangedTabs;


/** 
  Returns the first tab in the Tab View.
 @return The first tab in the Tab View. If the Tab View contain no tabs, returns nil.
 */
- (id) firstTab;


/** 
  Returns the last tab in the Tab View.
 @return The last tab in the Tab View. If the Tab View contain no tabs, returns nil.
 */
- (id) lastTab;


#pragma mark -
#pragma mark Selecting a Tab
//----------------------------------------
/** @name Selecting Tabs */
//----------------------------------------

/** 
  Select the given tab in the tabview.
 @param tab A tab contained in the Tab View.
 @see selectFirstTab:
 @see selectLastTab:
 @see selectNextTab:
 @see selectPreviousTab:
 */
- (void) selectTab: (id) tab;


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
- (SFTab *) selectedTab;

#pragma mark -
#pragma mark Ordering Tabs
//----------------------------------------
/** @name Ordering Tabs */
//----------------------------------------
/**
 Moves tab to new position.
 
 If new index is out of range, will be truncated to `0` or `count`.
 
 @param tab Tab to move.
 @param index New position of tab.
 */
- (void)moveTab:(id)tab toIndex:(NSUInteger)index;


#pragma mark -
#pragma mark Scrolling
//----------------------------------------
/** @name Scrolling */
//----------------------------------------

/** 
  Scroll the Tab View until tab is fully visibile.
 @param tab A tab contained in the Tab View.
 
 This method will scroll the Tab View using the default animation.
 
 @see scrollToTab:animated:
 */
- (void) scrollToTab: (id) tab;


/** 
  Scroll the Tab View until tab is fully visibile.
 @param tab A tab contained in the Tab View.
 @param animated Specify YES to animate the transition or NO if you do not want the transition to be animated.
 
 @see scrollToTab:
 */
- (void) scrollToTab: (id) tab animated: (BOOL) animated;
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
- (void)resizeTabs;

@end

