//
//  EditPreferences.h
//  SubEthaEdit
//
//  Created by Dominik Wagner on Mon Oct 07 2004.
//  Copyright (c) 2004 TheCodingMonkeys. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "TCMPreferenceModule.h"

@class DocumentModePopUpButton;

@interface StylePreferences : TCMPreferenceModule

@property (nonatomic, strong) IBOutlet DocumentModePopUpButton *O_modePopUpButton;
@property (nonatomic, strong) IBOutlet NSObjectController *O_modeController;
@property (nonatomic, strong) IBOutlet NSObjectController *O_fontController;

@property (nonatomic, strong) IBOutlet NSButton *O_fontDefaultButton;

@property (nonatomic, strong) IBOutlet NSButton *O_styleSheetDefaultRadioButton;
@property (nonatomic, strong) IBOutlet NSButton *O_styleSheetCustomRadioButton;
@property (nonatomic, strong) IBOutlet NSButton *O_styleSheetCustomForLanguageContextsRadioButton;
@property (nonatomic, strong) IBOutlet NSPopUpButton *O_styleSheetCustomPopUpButton;
@property (nonatomic, strong) IBOutlet NSView *O_customStyleSheetsContainerView;

@property (nonatomic, strong) IBOutlet NSBox *O_styleContainerBox;
@property (nonatomic, strong) IBOutlet NSBox *O_previewContainerBox;

@property (nonatomic, strong) IBOutlet NSTableView *O_customStylesForLanguageContextsTableView;

@property (nonatomic, strong) IBOutlet NSTextView *O_syntaxSampleTextView;

// properties for localization
@property (nonatomic, strong) IBOutlet NSBox *O_fontContainerBox;
@property (nonatomic, strong) IBOutlet NSButton *O_changeFontButton;
@property (nonatomic, strong) IBOutlet NSTextField *O_fontLabel;
@property (nonatomic, strong) IBOutlet NSButton *O_applyToOpenDocumentsButton;

- (IBAction)changeMode:(id)aSender;

- (IBAction)validateDefaultsState:(id)aSender;
- (IBAction)changeDefaultState:(id)aSender;

- (IBAction)styleRadioButtonAction:(id)aSender;

- (IBAction)changeCustomStyleSheet:(id)aSender;
- (IBAction)changeFontViaPanel:(id)sender;

- (IBAction)applyToOpenDocuments:(id)aSender;

@end
