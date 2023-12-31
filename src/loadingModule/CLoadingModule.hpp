#ifndef C_LOADING_MODULE_H
#define C_LOADING_MODULE_H

#include "common/Types.hpp"
#include "dataStructures/CDataManager.hpp"
#include "loadingModule/resourceLoader/CResourceLoader.hpp"

#include <QObject>
#include <QPointer>
#include <QStatusBar>

#include <map>
#include <memory>
#include <string>
#include <vector>

/**
 * @brief Class that represents a whole loading process.
 */
class CLoadingModule : public QObject
{
    Q_OBJECT

  public:
    /**
     * @brief Constructor.
     * @param aModuleType: Type of the module we want to construct.
     * @param aDataManager: reference to the data manager.
     * @param aStatusBar: Reference to CMainWindow's StatusBar.
     */
    CLoadingModule(Types::eLoadingModule aModuleType, CDataManager& aDataManager, QStatusBar& aStatusBar);

    /**
     * @brief Starts the loading process.
     */
    void LaunchLoadingModule();

    /**
     * @brief Asks current loading proces to stop (if there is one).
     */
    void LaunchCancelLoad();

    /**
     * @brief Returns whether this module has started loading.
     * @return True if module is yet to be loaded, false othersise.
     */
    [[nodiscard]] bool IsUnLoaded() const;

    /**
     * @brief Returns whether this modules is currently loading.
     * @return True if module is loading, false otherwise.
     */
    [[nodiscard]] bool IsLoading() const;

    /**
     * @brief Returns whether we are currenty canceling the load of this module.
     * @return True if we are caneling, false otherwise.
     */
    [[nodiscard]] bool IsCanceling() const;

    /**
     * @brief Returns whether this module is fully loaded.
     * @return True if module finished loading, false otherwise.
     */
    [[nodiscard]] bool IsLoaded() const;

  public slots:
    /**
     * @brief Gets called when a given resource loader finished.
     * @param aErrorCode: error code we want to notify.
     * @patam aErrorMessage: a brief message describing the error.
     */
    void ResourceLoaderFinished(int aErrorCode, QString aErrorMessage);

  signals:
    /**
     * @brief Signal to signalize that the module has finished loading.
     * @param aModuleType Type of the module that has finished.
     */
    void FinishedSignal(Types::eLoadingModule aType);

    /**
     * @brief Signal to notify loading module cancel finished.
     */
    void LoadInterrupted();

  private:
    /**
     * @brief Enum describing possible states of the loading module.
     */
    enum class eLoadingStatus
    {
        UnLoaded = 0, //!< Loading has not started.
        Loading,      //!< Loading is in progress.
        Canceling,    //!< We are cancelling the loading.
        Loaded,       //!< Loading has finished.
        Size          //!< Size of this enum.
    };

    using tResourcesMap = std::map<Types::eResource, QPointer<CResourceLoader>>; //!< Type that relates a resource type to its loader.

  private:
    /**
     * @brief Launches the loading process for a given resource.
     * @param The resource we want to load.
     */
    void LaunchResourceLoader(Types::eResource aResource);

    /**
     * @brief Manages the finishing of the loading of the module.
     */
    void LoadFinished();

  private:
    u8                    mResourceIndex; //!< Indicates which resource we are loading.
    Types::eLoadingModule mModuleType;    //!< Indicates type of this module.
    eLoadingStatus        mLoadingStatus; //!< Indicates the current loading status of the module.
    CDataManager&         mDataManager;   //!< Reference to the data manager.
    QStatusBar&           mStatusBar;     //!< Bar that shows messages at the bottom of the screen.

    tResourcesMap mResourceLoaders; //!< Current resource loader thread.
};

#endif // C_LOADING_MODULE_H
