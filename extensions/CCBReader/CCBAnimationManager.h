#ifndef __CCB_CCBANIMATION_MANAGER_H__
#define __CCB_CCBANIMATION_MANAGER_H__

#include "cocos2d.h"
#include "ExtensionMacros.h"
#include "CCBSequence.h"
#include "CCBValue.h"
#include "CCBSequenceProperty.h"

NS_CC_EXT_BEGIN

class CCBAnimationManagerDelegate
{
public:
    virtual void completedAnimationSequenceNamed(const char *name) = 0;
};

class CCBAnimationManager : public Object
{
private:
    Array *mSequences;
    Dictionary *mNodeSequences;
    Dictionary *mBaseValues;
    int mAutoPlaySequenceId;
    
    Node *mRootNode;
    
    Size mRootContainerSize;
    
    CCBAnimationManagerDelegate *mDelegate;
    CCBSequence *mRunningSequence;
    
    Array *mDocumentOutletNames;
    Array *mDocumentOutletNodes;
    Array *mDocumentCallbackNames;
    Array *mDocumentCallbackNodes;
    Array *mKeyframeCallbacks;
    Dictionary *mKeyframeCallFuncs;

    std::string mDocumentControllerName;
    std::string lastCompletedSequenceName;

    SEL_CallFunc mAnimationCompleteCallbackFunc;
    Object *mTarget;
    
    
public:
    bool jsControlled;
    CCBAnimationManager();
    ~CCBAnimationManager();


    Object *mOwner;
    
    virtual bool init();
    
    Array* getSequences();
    void setSequences(Array* seq);

    
    int getAutoPlaySequenceId();
    void setAutoPlaySequenceId(int autoPlaySequenceId);
    
    Node* getRootNode();
    void setRootNode(Node* pRootNode); // weak reference    
    

    void addDocumentCallbackNode(Node *node);
    void addDocumentCallbackName(std::string name);
    void addDocumentOutletNode(Node *node);
    void addDocumentOutletName(std::string name);

    void setDocumentControllerName(const std::string &name);
    
    std::string getDocumentControllerName();
    Array* getDocumentCallbackNames();
    Array* getDocumentCallbackNodes();
    Array* getDocumentOutletNames();
    Array* getDocumentOutletNodes();
    std::string getLastCompletedSequenceName();
    
    Array* getKeyframeCallbacks();
    
    const Size& getRootContainerSize();
    void setRootContainerSize(const Size &rootContainerSize);
    
    CCBAnimationManagerDelegate* getDelegate();
    void setDelegate(CCBAnimationManagerDelegate* pDelegate); // retain
    
    const char* getRunningSequenceName();
    
    const Size& getContainerSize(Node* pNode);
    
    void addNode(Node *pNode, Dictionary *pSeq);
    void setBaseValue(Object *pValue, Node *pNode, const char *pPropName);
    void moveAnimationsFromNode(Node* fromNode, Node* toNode);

    /** @deprecated This interface will be deprecated sooner or later.*/
    CC_DEPRECATED_ATTRIBUTE void runAnimations(const char *pName, float fTweenDuration);
    /** @deprecated This interface will be deprecated sooner or later.*/
    CC_DEPRECATED_ATTRIBUTE void runAnimations(const char *pName);
    /** @deprecated This interface will be deprecated sooner or later.*/
    CC_DEPRECATED_ATTRIBUTE void runAnimations(int nSeqId, float fTweenDuraiton);

    void runAnimationsForSequenceNamedTweenDuration(const char *pName, float fTweenDuration);
    void runAnimationsForSequenceNamed(const char *pName);
    void runAnimationsForSequenceIdTweenDuration(int nSeqId, float fTweenDuraiton);

    void setAnimationCompletedCallback(Object *target, SEL_CallFunc callbackFunc);

    void debug();
    
    void setCallFunc(CallFunc *callFunc, const std::string &callbackNamed);

    Object* actionForCallbackChannel(CCBSequenceProperty* channel);
    Object* actionForSoundChannel(CCBSequenceProperty* channel);
    
private:
    Object* getBaseValue(Node *pNode, const char* pPropName);
    int getSequenceId(const char* pSequenceName);
    CCBSequence* getSequence(int nSequenceId);
    ActionInterval* getAction(CCBKeyframe *pKeyframe0, CCBKeyframe *pKeyframe1, const char *pPropName, Node *pNode);
    void setAnimatedProperty(const char *pPropName, Node *pNode, Object *pValue, float fTweenDuraion);
    void setFirstFrame(Node *pNode, CCBSequenceProperty *pSeqProp, float fTweenDuration);
    ActionInterval* getEaseAction(ActionInterval *pAction, int nEasingType, float fEasingOpt);
    void runAction(Node *pNode, CCBSequenceProperty *pSeqProp, float fTweenDuration);
    void sequenceCompleted();
};

class CCBSetSpriteFrame : public ActionInstant
{
public:
    /** creates a Place action with a position */
    static CCBSetSpriteFrame* create(SpriteFrame *pSpriteFrame);

    ~CCBSetSpriteFrame();
    
    bool initWithSpriteFrame(SpriteFrame *pSpriteFrame);

    // Overrides
    virtual void update(float time) override;
	virtual CCBSetSpriteFrame* clone() const override;
	virtual CCBSetSpriteFrame* reverse() const override;

private:
    SpriteFrame *mSpriteFrame;
};


class CCBSoundEffect : public ActionInstant
{
public:
    static CCBSoundEffect* actionWithSoundFile(const std::string &file, float pitch, float pan, float gain);
    ~CCBSoundEffect();
    bool initWithSoundFile(const std::string &file, float pitch, float pan, float gain);

    // Overrides
    virtual void update(float time) override;
	virtual CCBSoundEffect* clone() const override;
	virtual CCBSoundEffect* reverse() const override;

private:
    std::string mSoundFile;
    float mPitch, mPan, mGain;
};


class CCBRotateTo : public ActionInterval
{
public:
    static CCBRotateTo* create(float fDuration, float fAngle);
    bool initWithDuration(float fDuration, float fAngle);

    // Override
    virtual void update(float time) override;
	virtual CCBRotateTo* clone() const override;
	virtual CCBRotateTo* reverse() const override;
    virtual void startWithTarget(Node *pNode) override;

private:
    float mStartAngle;
    float mDstAngle;
    float mDiffAngle;
};


class CCBRotateXTo: public ActionInterval
{
public:
    static CCBRotateXTo* create(float fDuration, float fAngle);
    bool initWithDuration(float fDuration, float fAngle);

    // Overrides
    virtual void startWithTarget(Node *pNode) override;
	virtual CCBRotateXTo* clone() const override;
	virtual CCBRotateXTo* reverse() const override;
    virtual void update(float time) override;

private:
    float mStartAngle;
    float mDstAngle;
    float mDiffAngle;
};


class CCBRotateYTo: public ActionInterval
{
public:
    static CCBRotateYTo* create(float fDuration, float fAngle);
    bool initWithDuration(float fDuration, float fAngle);

    // Override
    virtual void startWithTarget(Node *pNode) override;
	virtual CCBRotateYTo* clone() const override;
	virtual CCBRotateYTo* reverse() const override;
    virtual void update(float time) override;

private:
    float mStartAngle;
    float mDstAngle;
    float mDiffAngle;
};


class CCBEaseInstant : public ActionEase
{
public:
    static CCBEaseInstant* create(ActionInterval *pAction);

	virtual CCBEaseInstant* clone() const override;
	virtual CCBEaseInstant* reverse() const override;
    virtual void update(float dt) override;
};


NS_CC_EXT_END

#endif // __CCB_CCBANIMATION_MANAGER_H__
