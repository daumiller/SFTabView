//
//  SFTabViewDelegate.h
//  SFTabView
//
//  Created by Dillon Aumiller on 6/3/12.
//  Copyright (c) 2012 Dillon Aumiller. All rights reserved.
//

#import <Foundation/Foundation.h>
@class SFTabView;
@class SFTab;

/**
 The SFTabViewDelegate protocol defines the optional methods implemented by delegates of SFTabView objects. 
 */
@protocol SFTabViewDelegate
@optional
//////////////////////////////////////////////////////////////////////////////////////////
/// @name Selecting Tabs
//////////////////////////////////////////////////////////////////////////////////////////
/** 
 Sent to the delegate to allow or prohibit the specified tab to be selected.
 
 When a tab is clicked by the user, this method will be called on the delegate. 
 Returning NO will disallow that tab from being selected. Returning YES allows it to be selected.
 
 @see tabView:didSelectTab:
 @see tabView:willSelectTab:
 
 @param tabView The tab view that sent the message.
 @param tab The tab to be selected.
 
 @return YES if the tab selection should be allowed, otherwise NO.
 */
- (BOOL)tabView:(SFTabView *)tabView shouldSelectTab:(SFTab *)tab;


/** 
 Sent at the time the user clicked a tab in the Tab View.
 
 @see tabView:didSelectTab:
 @see tabView:willSelectTab:
 
 @param tabView The tab view that sent the message.
 @param tab The tab that was selected.
 */
- (void)tabView:(SFTabView *)tabView didSelectTab:(SFTab *)tab;

/** 
 Sent at the time the user clicked a tab in the Tab View, just before the tab will change state.
 
 @see tabView:shouldSelectTab:
 @see tabView:didSelectTab:
 
 @param tabView The Tab View that sent the message.
 @param tab The tab that will be selected.
 */
- (void)tabView:(SFTabView *)tabView willSelectTab:(SFTab *)tab;


//////////////////////////////////////////////////////////////////////////////////////////
/// @name Adding and Removing Tabs
//////////////////////////////////////////////////////////////////////////////////////////
/** 
 Sent after a new tab is added to the Tab View.
 
 @see tabView:didRemovedTab:
 
 @param tabView The Tab View that sent the message.
 @param tab The new tab added to the the Tab View.
 */
- (void)tabView:(SFTabView *)tabView didAddTab:(SFTab *)tab;


/** 
 Sent after a tab is deleted from the Tab View.
 
 @see tabView:didAddTab:
 
 @param tabView The Tab View that sent the message.
 @param tab The tab deleted from the the Tab View.
 */
- (void)tabView:(SFTabView *)tabView didRemovedTab:(SFTab *)tab;

@end
